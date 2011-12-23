/*******************************************************************************
 *
 *  FRAM_GUI.pde 
 *           - PC demo application for establishing a serial connection
 *             with the MSP-EXP430FR5739 Experimenter's Board.
 *
 *  Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 ******************************************************************************/

/******************************************************************************
 *       MSP-EXP430FR5739 FRAM Experimenter's BoardUser Experience GUI
 * Desc:
 * This PC GUI application communicates with the MSP-EXP430FR5739 specifically  
 * to receive FRAM write speed data from the MSP-EXP430FR5739 and provides
 * the visualization of said information in the GUI. The GUI will present write  
 * speeds to FRAM, remaining write endurance (assuming 512B memory block), and
 * LED status.
 * 
 * The GUI uses a small .NET utility (FindAppUART.exe) to automatically detect
 * a proper 430Emulator device connected to the PC USB port. Upon 
 * correct USB COM port discovery, the application initiates a 9600baud UART 
 * connection and starts receiving data. 
 * 
 * The MSP-EXP430FR5739 sends data via a simple '7-byte' protocol:
 *  Byte[0] = 250 - Preamble
 *  Byte[1] = Mode Number (1, 2, 3, 4) 
 *            Mode 1 - Each received packet signifies 100kB has been written to 
 *                     FRAM. This mode shows the high write speed of FRAM. The  
 *                     LEDs increment every 100kB written. (~1400-2000kB/s)
 *            Mode 2 - Each received packet signifies 2kB has been written to 
 *                     FRAM. This mode emulates the speed of Flash. The LEDs 
 *                     increment every 100kB written (~10-13kB/s)
 *            Mode 3 - Each received packet means 600B (0.6kB) has been read 
 *                     from the accelerometer sensor and written to FRAM
 *                   - The tilt data is represented on the 8 LEDs
 *            Mode 4 - Each received packet means 600 (0.6kB) has been read 
 *                     from the temperature sensor and written to FRAM
 *                   - The temp data is represented on the 8 LEDs
 *  Byte[2] = This tells me which LED is currently lit on the FRAM board [0-7]
 *  Byte[3] = 00 
 *  Byte[4] = 00
 *  Byte[5] = 00
 *  Byte[6] = 254 - END Byte
 *              
 * The GUI starts in a "finding connected devices" window. Once the FR5739 is
 * discovered, the GUI enters the main application. The GUI provides two
 * speedometers - One for FRAM write speed, and a 2nd one for emulated Flash 
 * write speeds. While all modes are writing to the FRAM block, Mode 2 is set
 * to emulate the max write speeds of a typical Flash MCU (~10-13kB/s)
 *    - Mode 1, 3, 4 - Show FRAM write speeds on the 1st Speedometer
 *    - Mode 2 - Emulates Flash write speeds on the 2nd Speedometer
 *    - The current speedometer displaying data is indicated by the GUI
 *    - As users switch between modes, the "last recorded" flash or FRAM speeds
 *      are saved on the speedometer so users can compare the speeds of FRAM
 *      vs Flash 
 *    - When in any mode, users can press SWITCH2 on the MSP-EXP430FR5739 board.
 *      This will enter a "ULP Measurement Mode". At this time, the LEDs on the 
 *      board are turned off and UART communication is turned off. This allows
 *      users to measure current consumption of the FRAM MCU during the various
 *      modes. 
 *      Pressing SWITCH2 again exits "ULP Measurement Mode" and will re-enter
 *      the previous mode.
 *    - In the GUI, when users press SWITCH2, the GUI stops updating (as no UART
 *      transmissions are being received). Pressing SWITCH2 again, we return
 *      to the previous mode. The GUI "resets" and assumes a starting time of  
 *      0 seconds and a starting endurance of 100%.
 *
 * In addition to the write speeds, the GUI shows remaining life endurance in 
 * percentage. The GUI assumes we are writing to a 512B memory block. Any time 
 * a user enters a mode, the endurance is reset to 100%
 *
 * The GUI also shows the same LED sequence shown on the FR5739 board. 
 *    - Mode 1 & 2- The LEDs increment for every 100kB that is written to FRAM
 *    - Mode 3 & 4- The LEDs show how far the sensor data has deviated from the 
 *      starting point.
 *
 *
 * A. Fernandez
 * Texas Instruments, Inc.
 * Ver 0.98 May 2011
 ******************************************************************************/ 

import processing.serial.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

//variables for serial port
int FR57xxComPortFound = 0, numberOfLookingDots=0;
Serial myPort;
int COMPort; // holds COMPort that FR57xx is connected to

//variables for reading buffer
int dataRead; // holds last read Byte
int [] inByte = new int[7]; // Holds the 7 bytes per packet
int [] dummy = new int[7]; // used to help clear out the buffer

//variables for LED update
int [] fillRect = new int[8]; // array storing current status of the 8 LEDs
int ledIndex=0; // index to cycle through fillRect
color led; // color of the Flash vs FRAM indicator

//variables for background & font
PImage backgroundStart; // holds background image for the "find connected devices" mode
PFont fontA; // holds font style/size
PImage bgFind, bg; // holds background image
String looking; // for cycling "..." when searching for connected FR5739

//variables for mode
int i, j, mode, prevMode=0;
String modeName;

//variables for speed & endurance calculations
float speed=0, inByteCount=0, timerStart=0, endurance=100, seconds, flashAngle=-205, framAngle=-205, framSpeed, flashSpeed, bitEndurance, speedFactor=0, shiftNeedle = 580;
int enduranceFRAM=100; 

//variables for updating GUI
int lastUpdate=0;

// variables for test
int test=0;

void findFR57xx() // find COMport that FR5739 is connected to
{
  String ComPortName ="";  
  try
  {
    Process proc = Runtime.getRuntime().exec(sketchPath+"/FindAppUART.exe"); 
    proc.waitFor();
    int exitVal = proc.exitValue();
    // Get the first line from the process' STDOUT
    BufferedReader buf = new BufferedReader(new InputStreamReader(proc.getInputStream()));
    ComPortName = buf.readLine();   
    if (ComPortName.substring(0,3).equals("COM") != true)
      ComPortName = "";
    else
    {
      FR57xxComPortFound = 1;  
      myPort = new Serial(this, ComPortName, 9600);  
    }
  }
  catch(Exception e)
  {
    println(e);    
  }   
}

void promptLookingForFR57xx() // If no FR57xx connected, update the "searching for connected devices" screen
{  
  fontA = loadFont("Consolas-16.vlw");
  noStroke();
  textFont(fontA, 20);
  textAlign(LEFT);
  numberOfLookingDots++;
  fill(60,60,60);
  rect(526,162,35,10);  
  
  fill(255);
  if (numberOfLookingDots==5)
    numberOfLookingDots = 1;    
  switch(numberOfLookingDots)
  {  
   case 1: looking = ""; break;
   case 2: looking = ". "; break;
   case 3: looking = ".. "; break;
   case 4: looking = "..."; break;
  }

}

// setup the "searching for connected devices" window. This setup function is called once at start up. Then, the draw() function gets called and loops.
void setup()
{
  background(0);
  
  //define size of GUI window (Same dimensions as the background image) 
  size(1052, 401); 
  smooth();

  //load font
  fontA = loadFont("Arial-BoldMT-48.vlw");  
  
  // load and display background image for "searching for connected devices" window
  backgroundStart = loadImage("BackgroundFind.png");  
  bg = loadImage("Background.png");
  image(backgroundStart,0,0); //display background

  // define font color, font style/size, and font alignment
  fill(255,0,0); 
  textFont(fontA, 25); 
  textAlign(LEFT); 
  text("MSP-EXP430FR5739 ", 30,45); 
  
  // define font color, font style/size, and font alignment
  fill(255);
  text("| FRAM User Experience Demo", 282,45);  
  textFont(fontA, 18);
  text("Please plug your MSP-EXP430FR5739 FRAM Experimenter's Board to your PC with included USB cable.",20,130); 

  //define framefrate for "searching for connected devices" window  
  frameRate(3);  
}

// Redraw the background of the main application. Also update the 8 LEDs.
void drawMainAppCanvas()
{  
    background(bg);
   
    // define color, placement, and size of the FRAM vs Flash LED indicator on GUI
    fill(129);
    ellipse(290,170, 20, 20);
    ellipse(857,170, 20, 20);
  
    //Update the 8 LEDs!
    fill(fillRect[0]);
    rect(450, 280, 8, 20);
    fill(fillRect[1]);
    rect(470, 280, 8, 20);
    fill(fillRect[2]);
    rect(490, 280, 8, 20);
    fill(fillRect[3]);
    rect(510, 280, 8, 20);
    fill(fillRect[4]);
    rect(530, 280, 8, 20);
    fill(fillRect[5]);
    rect(550, 280, 8, 20);
    fill(fillRect[6]);
    rect(570, 280, 8, 20);
    fill(fillRect[7]);
    rect(590, 280, 8, 20);

    //define the font style, size, and alignment for the rest of the application
    textFont(fontA, 12);
    textAlign(LEFT);   
}

// Search to see if the MSP-EXP430FR5739 board is plugged into the PC.
void lookForFR57xx()
{
      // Try to find connected MSP-EXP430FR5739 Experimenter's Board
      findFR57xx();
      // if not plugged in, update the "searching for connected devices" screen  
      if (FR57xxComPortFound == 0)
      {
        promptLookingForFR57xx(); // increment cycling "..."
        textFont(fontA, 18);
        fill(255, 255, 255);
        text("Looking for MSP-EXP430FR5739 Experimenter's Board "+ looking, 20,170); // update the scrolling "..."  
      }
      
      else  // PREPARE FOR MAIN APPLICATION 
      {
        frameRate(60);  
        led = color(254,169,6); // define color of the LED array
        drawMainAppCanvas();
      }
}

// Update the data in the center console including: mode, remaining endurance, time spent in mode.
void drawCenterConsole()
{
    stroke(255);
    fill(255);
    textFont(fontA, 16);  
    if(mode==85) 
      text("Mode: ULP measure", 435, 125);
    else
      text("Mode: "+mode, 435, 125);
    textFont(fontA, 12);   
    text(modeName, 435, 140);

    textFont(fontA, 16);      
    text("Remaining Endurance: ",435,170);
    textFont(fontA, 12);   
    text("(Assuming 512B mem. block)", 435, 185);
    if(mode == 2){
      if(endurance<=0){
        text("Endurance is depleted", 435, 200);
      }
      else{
        text(endurance, 435, 200);
        text("%",480,200);
      }
    }
    else if(mode == 1 || mode ==3 || mode ==4){
      text("99.9999"+enduranceFRAM, 435, 200);
      text("%",540,200);
    }
    else if(mode == 85){
      if(prevMode == 2){
        text(endurance, 435, 200);
        text("%",480,200);
      }
      else if(prevMode == 1 || prevMode ==3 || prevMode ==4){
        text("99.9999999"+enduranceFRAM, 435, 200);
        text("%",530,200);
      }
    }

    textFont(fontA, 16);   
    text(framSpeed, 165, 316);
    text("kB/s", 256, 316);

    text(flashSpeed, 184+shiftNeedle, 316);
    text("kB/s", 250+shiftNeedle, 316);
    
    if(timerStart != 0 && endurance >0 && mode>0 && mode<5)
      seconds = (millis()-timerStart)/1000;
      
    fill(255,255,255);  
    textFont(fontA, 16);  
    text("Time spent in mode: ",435,230);
    textFont(fontA, 12);   
    text(seconds, 435,245);   
    text("seconds", 490, 245);
  
}

//Update the speedometer needle position. Also update the LED indicator for Flash or FRAM
void drawSpeedometer()
{
  //draw Speedometer needle
  stroke(0, 0, 0);
  if(mode==1 || mode==3 || mode==4){ //Update FRAM speedometer when in Mode 1, 3, 4
    fill(254,169,6);
    ellipse(290,170, 20, 20);
    fill(220);
    ellipse(857,170, 20, 20);
    framAngle=0.114*framSpeed-205;
    if(framAngle >25){//cap the needle at ~2000kB/s
      framAngle = 25;
    }
  }
  
  if(mode==2){ //Update "Flash" speedometer when in Mode 2
    fill(254,169,6);
    ellipse(857,170, 20, 20);
    fill(220);
    ellipse(290,170, 20, 20);
    flashAngle=0.114*flashSpeed-205;
  }
  
  fill(255, 0, 0); 
  pushMatrix(); //FRAM needle angle 
  translate(237, 251); 
  rotate(radians(framAngle));
  rect(0, 0, 160, 5);
  popMatrix();
  
  pushMatrix(); //flash needle angle 
  translate(237+shiftNeedle, 251); 
  rotate(radians(flashAngle));
  rect(0, 0, 160, 5);
  popMatrix();
}
    

// This is our main loop. This function is called/looped and defined by "frameRate(60)" <-- 60fps
void draw()
{
  
  if (FR57xxComPortFound==0) //if no FR57xx board is found, continue to search
    lookForFR57xx();
  else // we found the FR57xx device plugged in!
  {    
    dataRead = myPort.read(); //read in next byte in buffer
    
    if (dataRead == 250)  //250 = Header/preamble of our 7-byte packet. This is a possible start of new packet!
    { 
      for(j=1; j<7; j++) //read in the next 6 bytes
        inByte[j] = myPort.read();
        
      if((inByte[1] == 1) || (inByte[1] == 2) || (inByte[1] == 3) || (inByte[1] == 4) || (inByte[1]==85)) //check to see if a valid mode is sent in the packet (1, 2 or 3).
      {
        prevMode = mode; //Remember previous Mode 
        mode = inByte[1];    
        
        if (mode != prevMode) // check if we're in a new mode. If so, reset
        {
          inByteCount = 0;
          timerStart=millis();
        }
        
        inByteCount=inByteCount+1;  // received a packet!  
        
        if(mode == 1) // Define the LED update properties for mode 1 (The LEDs increment up the LEDs for every 100kB written to FRAM)
        {
          
          speedFactor = 100; // update factor to tell us how many kB were written for each packet
          bitEndurance = 1000000000;  // 1,000,000,000*10,000 = 100,000,000,000,000
          modeName = "FRAM high-speed write test";
          enduranceFRAM = 100000000-int((inByteCount*1*1000000000)/(512*1000000000));  // Looking at just 1%
          framSpeed = (inByteCount*speedFactor*1000)/(millis()-timerStart);
          
          ledIndex = inByte[2]; // Figure out which LEDs should be lit
          if(ledIndex>=0 && ledIndex<=7){
            for(j=0; j<8; j++)  //clear all LEDs
              fillRect[j] = 28;
            for(j=0; j<=ledIndex; j++) //Set up the LEDs that should be lit
              fillRect[j] = led;  
          }
        }
        
        else if(mode == 2) // Define the LED update properties for mode 2 (The LEDs increment up the LEDs for every 2kB written to FRAM)
        {
                    
          speedFactor = 2; // update factor to tell us how many kB were written for each packet
          modeName = "Flash write speed emulation";
          endurance = 100-((inByteCount*2000)*100/(512*10000));
          flashSpeed = (inByteCount*speedFactor*1000)/(millis()-timerStart);          
          
          ledIndex = inByte[2]; //sent for every 2kB. LED should only toggle every 100kB --> Each inByteCount correlates to 2kB written. So every 50x inByteCounts = 100kB
          if(ledIndex>=0 && ledIndex<=7){
            for(j=0; j<8; j++)  //reset LED sequence
              fillRect[j] = 28;
            for(j=0; j<=ledIndex; j++) //Set up the LEDs that should be lit
              fillRect[j] = led;
          }
        }
        
        else if(mode == 3){ // sample the accelerometer data, display on 8LEDs and show instantaneous speed/endurance
          speedFactor = 0.6; // update factor to tell us how many kB were written for each packet. Every 300 samples (2bytes/sample) we should get a packet
          modeName = "Write accel. data to FRAM";
          enduranceFRAM = 100000000-int((inByteCount*1*1000000000)/(512*1000000000));  // Looking at just 1%
          framSpeed = (inByteCount*speedFactor*1000)/(millis()-timerStart);
          
          framSpeed = framSpeed*(17.5/11.7); // factor to compensate for the time lost during UART transmission
          /*
          UART packet = 7*8*1/9600 = 5.8ms  
          600 bytes (300 samples) + UART packet = 17.5ms (measured)
          600 bytes = 17.5-5.8 = 11.7ms
          Speed = 600*1000/11.7 = 51kBps
          Factor = 17.5/11.7
          */
          

          ledIndex = inByte[2]; //sent for every 2kB. LED should only toggle every 100kB --> Each inByteCount correlates to 2kB written. So every 50x inByteCounts = 100kB
                    
          if(ledIndex<3 && ledIndex>=0){
            for(j=0; j<=7; j++) //reset LED sequence
              fillRect[j] = 28;            
            for(j=ledIndex; j<=4; j++)  //turn on LEDs
              fillRect[j] = led;
          }
          else if(ledIndex>4 && ledIndex<=7){
            for(j=0; j<=7; j++) //reset LED sequence
              fillRect[j] = 28;            
            for(j=3; j<=ledIndex; j++)  //turn on LEDs
              fillRect[j] = led;
          }
          else if(ledIndex == 52){//52 decimal = 0x34
            for(j=0; j<=7; j++) //Set up the LEDs that should be lit
              fillRect[j] = 28;            
              fillRect[3] = led;
              fillRect[4] = led;
          }

        }
        
        else if(mode == 4){ // sample the temp data, display on 8LEDs and show instantaneous speed/endurance
          speedFactor = 0.6; // update factor to tell us how many kB were written for each packet. Every 300 samples (2bytes/sample) we should get a packet
          modeName = "Write temp. data to FRAM";
          enduranceFRAM = 100000000-int((inByteCount*1*1000000000)/(512*1000000000));  // Looking at just 1%
          framSpeed = (inByteCount*speedFactor*1000)/(millis()-timerStart);
          framSpeed = framSpeed*(23/17.2); // factor to compensate for the time lost during UART transmission
          /*
          UART packet = 7*8*1/9600 = 5.8ms
          600 bytes + UART packet = 23ms (measured)
          600 bytes = 23ms – 5.8ms = 17.2
          Speed = (1000/17.2)*600 = 34.88kbps
          Factor = 23/17.2
          */


          ledIndex = inByte[2]; //sent for every 2kB. LED should only toggle every 100kB --> Each inByteCount correlates to 2kB written. So every 50x inByteCounts = 100kB
          
          if(ledIndex<3 && ledIndex>=0){
            for(j=0; j<=7; j++) //reset LED sequence
              fillRect[j] = 28;            
            for(j=ledIndex; j<=4; j++)  //turn on LEDs
              fillRect[j] = led;
          }
          else if(ledIndex>4 && ledIndex<=7){
            for(j=0; j<=7; j++) //reset LED sequence
              fillRect[j] = 28;            
            for(j=3; j<=ledIndex; j++)  //turn on LEDs
              fillRect[j] = led;
          }
          else if(ledIndex == 52){//52 decimal = 0x34
            for(j=0; j<=7; j++) //Set up the LEDs that should be lit
              fillRect[j] = 28;            
              fillRect[3] = led;
              fillRect[4] = led;
          }
        }
        
        if(mode==85){ // trying to enter ULP measurement mode. Need to stop time. record time entering ULP measurement mode. 
          for(j=0; j<=7; j++) //reset LED sequence
            fillRect[j] = 28;   
        }
        

        drawMainAppCanvas(); //Update 8 LEDs
        drawCenterConsole(); //Update center console
        drawSpeedometer();   //Update the speedometer needle
        textFont(fontA, 12); 

      }

    }
    
  textAlign(LEFT);
  fill(38,38,38);
  stroke(38,38,38);
  rect(968,13, 68, 50);
  fill(255);
  text(frameRate, 968, 23);
  text("fps", 1014, 23);
  test=myPort.available();
  text(test, 1014, 40);
  text("Buffer", 971, 40);
  }
  
}


