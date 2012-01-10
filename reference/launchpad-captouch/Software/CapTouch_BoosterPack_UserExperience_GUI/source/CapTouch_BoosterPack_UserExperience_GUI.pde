/*******************************************************************************
 *
 *  CapTouch_BoosterPack_UserExperience_GUI.pde 
 *           - PC demo application for establishing a serial connection
 *             with the LaunchPad CapTouch BoosterPack.
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
 *         MSP430G2-LaunchPad CapTouch BoosterPack User Experience GUI
 * Desc:
 * This PC GUI application communicates with the LaunchPad specifically to 
 * receive capacitive touch data from the LaunchPad CapTouch BoosterPack and 
 * provides the visualization of said information in the GUI.   
 *  
 * The GUI uses a small .NET utility (FindAppUART.exe) to automatically detect
 * a proper LaunchPad/430Emulator device connected to the PC USB port. Upon 
 * correct USB COM port discovery, the application initiates a 9600baud UART 
 * connection and starts receiving data. 
 * 
 * Upon each LaunchPad event, data is transmitted [always] via a simple '2-byte' 
 * protocol as described below.
 * [LaunchPad]  Wake up       :    0xBE 0xEF 
 * [LaunchPad]  Sleep         :    0xDE 0xAD 
 * [CapTouch]   Center Button :    0x80 0x80
 * [CapTouch]   Wheel Tap     :    WT   WT  = pos. on wheel [0-0x0F] + 0x30
 * [CapTouch]   Gesture Start :    0xFC POS = pos. on wheel [0-0x0F] + 0x20
 * [CapTouch]   Gesture Stop  :    0xFB POS = pos. on wheel [0-0x0F] + 0x20
 * [CapTouch]   Gesture Update:    GES  POS 
 *     Gesture = [0-0x0F]        --> Clockwise gesture 
 *              = 0x10+ [0-0x0F]  --> Counter-clockwise gesture 
 *              
 * The GUI grays out during sleep mode and returns to active mode upon wake up.
 * The 'Center Button' press data toggles the center circle color, mimicking the 
 * behavior of the center LED on the BoosterPack.
 * The 'Wheel Tap' is represented by lighting up a single slice on the wheel.
 * The gesture tracking [Start, Stop, Update] is visualized on the wheel with 
 * the coloration of the wheel slices. Gesture can be tracked for several 
 * revolutions of the wheel, in both clockwise and counter-clockwise directions.
 * 
 * A hidden code/lock is embedded in the wheel. Correct sequence [similar to a
 * rotational combination lock] reveals a secret address.
 * 
 * D. Dang
 * Texas Instruments, Inc.
 * Ver 0.90 Feb 2011
 ******************************************************************************/ 
 
import pitaru.sonia_v2_9.*;
import processing.serial.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

final int TIME_OUT = 140;

/*--------Dimensions & coordinates------------*/
final int CANVAS_SIZE_X = 900;
final int CANVAS_SIZE_Y = 580;
final int OUT_CIRCLE_RADIUS = 248;
final int IN_CIRCLE_RADIUS = 101;
final int CENTER_CIRCLE_RADIUS = 37;
final int CIRCLE_CENTER_X = 450;
final int CIRCLE_CENTER_Y = 285;

final int SOUND_ICON_X = 820;
final int SOUND_ICON_Y = 20;

/*--------Drawing definitions------------*/
final int NUMBER_OF_SLICES = 16;
final int BACKGROUND_COLOR = 170;
final int TAP_SLICE_COLOR = -100;
final int SLICE_TRANSPARENCY = 30;
final int SLICE_TRANSPARENCY_OFFSET = 80;

/*--------UART protocol definitions------------*/
final int WAKE_UP_UART_CODE       =  0xBE;
final int WAKE_UP_UART_CODE2      =  0xEF;
final int SLEEP_MODE_UART_CODE    =  0xDE;
final int SLEEP_MODE_UART_CODE2   =  0xAD;
final int CENTER_BUTTON_CODE      =  0x80;
final int INVALID_WHEEL_POSITION  =  0xFE;
final int INVALID_GESTURE         =  0xFD;
final int GESTURE_START           =  0xFC;
final int GESTURE_STOP            =  0xFB;
final int GESTURE_POSITION_OFFSET =  0x20;
final int WHEEL_POSITION_OFFSET   =  0x30;
final int NUMBER_OF_WHEEL_POSITIONS = 16;
//final int INVALID_WHEEL_POSITION  = -100;
final int INVALID_GESTURE_DIRECTION = -100;
final int GESTURE_CLOCKWISE = 1;
final int GESTURE_COUNTERCLOCKWISE = -1;




/*----------CapTouch-related variables----------------*/
int gestureStartingPosition = INVALID_WHEEL_POSITION, gestureStoppingPosition = INVALID_WHEEL_POSITION;
int[] gestureCoverPositions = new int[16];
int gestureDirection = INVALID_GESTURE_DIRECTION;
int gestureImmediateDirection = INVALID_GESTURE_DIRECTION;

int allLit = 0;
int inactivityCounter=0, sleeping=0, tapping=0, centerButton=0;
int CenterButtonToggle=0;

/*------Serial communication----------------*/
int LaunchPadComPortFound = 0, numberOfLookingDots=0;
Serial LaunchPad;

/*--------- Visual & audio elements-----------*/
PImage backgroundImage, innerCircleImage,innerCircleSelectedImage, innerCircleUnlockedImage ;
int drawNumberEnabled = 0;

Sample click,clickFound, clickOpen;
int soundEnabled = 0;


void drawSlice(int sliceIndex, int sliceLevel)
{
  int sliceAfter, sliceLabel;
  sliceLabel = sliceIndex;  
  if (sliceIndex < 3)
    sliceIndex = sliceIndex + 16 - 4;
  else
    sliceIndex = sliceIndex - 4;    
  sliceAfter = sliceIndex + 1;  
  if (sliceAfter == NUMBER_OF_SLICES)
    sliceAfter = 0;
  noStroke();
  stroke(255);
  strokeWeight(4);
  if (sliceLevel == TAP_SLICE_COLOR)
    fill(160,160,160,  225);
  else
    fill(252,236,54, sliceLevel * SLICE_TRANSPARENCY + SLICE_TRANSPARENCY_OFFSET);    
  arc(CIRCLE_CENTER_X, CIRCLE_CENTER_Y,  OUT_CIRCLE_RADIUS*2, OUT_CIRCLE_RADIUS*2, (((float)sliceIndex)-0.5) * 2 * PI /16,  (((float)sliceIndex)+0.5) * 2 * PI /16);  
  line( CIRCLE_CENTER_X + cos( (((float)sliceIndex)-0.5)  * 2 * PI /16  ) * OUT_CIRCLE_RADIUS, CIRCLE_CENTER_Y + sin((((float)sliceIndex)-0.5)  * 2 * PI /16  ) * OUT_CIRCLE_RADIUS,
  CIRCLE_CENTER_X + cos( (((float)sliceIndex)-0.5)  * 2 * PI /16  ) * IN_CIRCLE_RADIUS, CIRCLE_CENTER_Y + sin((((float)sliceIndex)-0.5)  * 2 * PI /16  ) * IN_CIRCLE_RADIUS); 
  line( CIRCLE_CENTER_X + cos( (((float)sliceIndex)+0.5)  * 2 * PI /16  ) * OUT_CIRCLE_RADIUS, CIRCLE_CENTER_Y + sin((((float)sliceIndex)+0.5)  * 2 * PI /16  ) * OUT_CIRCLE_RADIUS,
  CIRCLE_CENTER_X + cos( (((float)sliceIndex)+0.5)  * 2 * PI /16  ) * IN_CIRCLE_RADIUS, CIRCLE_CENTER_Y + sin((((float)sliceIndex)+0.5)  * 2 * PI /16  ) * IN_CIRCLE_RADIUS); 
  if (drawNumberEnabled == 1)
  {
    fill(0);
    text( sliceLabel,
          CIRCLE_CENTER_X + cos( (((float)sliceIndex))  * 2 * PI /16  ) * (OUT_CIRCLE_RADIUS-40)-7,
          CIRCLE_CENTER_Y + sin( (((float)sliceIndex))  * 2 * PI /16  ) * (OUT_CIRCLE_RADIUS-40));    
  }
}
void drawCanvas()
{
  int i;
      background(BACKGROUND_COLOR);    
      image(backgroundImage, 0 ,0);
      fill(0,0,0,255);      
      if (unlocked == 1)
      {
        fill(0);
          text("BoosterPack Unlocked",300,30);  
          
          for (i=0;i<4;i++)
              drawSlice(code[i],4);
           fill(255);
          ellipse(CIRCLE_CENTER_X, CIRCLE_CENTER_Y, IN_CIRCLE_RADIUS*2 , IN_CIRCLE_RADIUS*2);  
          image(innerCircleUnlockedImage, 0, 0);
      }
      
}

void goToSleep()
{
  tint(120,120,120,180);
  drawCanvas();
  tint(120,120,120,180);
  fill(255);
  textSize(20);            
  text(".",20,30);
  text(".",28,30);
  text(".",35,30);
  textSize(25);
  text("z",47,30);
  textSize(30);
  text("z",65,30);
  textSize(35);
  text("z",85,30);
  textSize(40);
  text("z",108,30);
  textSize(30);
  noTint();
  sleeping = 1;
  inactivityCounter = TIME_OUT;       
}

void findLaunchPad()
{
  String ComPortName ="";  
  try
  {
    Process proc = Runtime.getRuntime().exec("FindAppUART.exe"); 
    proc.waitFor();
    int exitVal = proc.exitValue();
    // Get the first line from the process' STDOUT
    BufferedReader buf = new BufferedReader(new InputStreamReader(proc.getInputStream()));
    ComPortName = buf.readLine();    
    if (ComPortName.substring(0,3).equals("COM") != true)
      ComPortName = "";
    else
    {
      LaunchPadComPortFound = 1;  
       LaunchPad = new Serial(this, ComPortName, 9600);  
    }
  }
  catch(Exception e)
  {
    println(e);    
  }   
}

void promptLookingForLaunchPad()
{  
  fill(255,0,0);
  noStroke();
  rect(100,CANVAS_SIZE_Y/2-100,CANVAS_SIZE_X-120,200);
  fill(255);
  textSize(50);
  numberOfLookingDots++;
  if (numberOfLookingDots==5)
    numberOfLookingDots = 1;    
  switch(numberOfLookingDots)
  {  
   case 1: text("Looking for LaunchPad    ", 175,CANVAS_SIZE_Y/2 ); break;
   case 2: text("Looking for LaunchPad .  ", 175,CANVAS_SIZE_Y/2 ); break;
   case 3: text("Looking for LaunchPad .. ", 175,CANVAS_SIZE_Y/2 ); break;
   case 4: text("Looking for LaunchPad ...", 175,CANVAS_SIZE_Y/2 ); break;
  }

}
void setup() 
{
  size(CANVAS_SIZE_X, CANVAS_SIZE_Y);
  background(255,0,0);
  Sonia.start(this);
  click = new Sample("click1.aiff");   
  clickOpen = new Sample("open.aiff");
  clickFound = new Sample("unlock.aiff");
  click.setVolume(3);
  clickFound.setVolume(3);
  frameRate(3);

  backgroundImage = loadImage("background.png");
  innerCircleImage = loadImage("innerCircle.png");
  innerCircleSelectedImage = loadImage("innerCircleSelected.png");
  innerCircleUnlockedImage = loadImage("innerCircleUnlocked.png");
 

  
  findLaunchPad();
  if (LaunchPadComPortFound == 0)
  {
    fill(255);
    textSize(40);
    text("LaunchPad Capacitive Touch BoosterPack", 70,50); 
    textSize(55);
    fill(0);
    text("User Experience Demo", 150,100); 
  
    fill(0);  
    textSize(25);
    text("1. Plug your Capacitive Touch BoosterPack into the LaunchPad", 150,CANVAS_SIZE_Y - 70); 
    text("2. Connect your LaunchPad to the PC via USB", 150,CANVAS_SIZE_Y - 45); 
    promptLookingForLaunchPad();
  }
  else
  {
    frameRate(30);    
    goToSleep();    
  }
}



void draw() 
{
  int i;
  if (LaunchPadComPortFound==0)
  {
    findLaunchPad();
    if (LaunchPadComPortFound==1)
    {
       goToSleep();
       frameRate(30);
    }
    else
      promptLookingForLaunchPad();
    
  }
  else
  
  if(LaunchPad.available() >= 0) 
  {    
    int buf, buf1;
    buf  = LaunchPad.read(); 
    buf1 = -1;
    
    if (buf>=0)
    {  
      drawCanvas();
      textSize(30);
      
      sleeping = 0;
      inactivityCounter=0;
      tapping = 0 ;
      centerButton = 0;
      switch(buf)
      {   
      case WAKE_UP_UART_CODE:        

                    while (buf1 <0)
                      buf1 = LaunchPad.read();      
                    if (buf1==WAKE_UP_UART_CODE2)
                      text("Proximity Sensor Wake Up",20,30);  
                    else
                    {
                      print("Error: invalid UART Wake up == ");                        
                      println(buf1);
                    }
                    break;         
                    
      case SLEEP_MODE_UART_CODE:
                   while (buf1 <0)
                      buf1 = LaunchPad.read();      
                    if (buf1==SLEEP_MODE_UART_CODE2)
                    {
                      //tint(120,0,0,180);
                      CenterButtonToggle = 0;
                      backgroundImage = loadImage("background.png");
                      innerCircleImage = loadImage("innerCircle.png");
                      tint(120,120,120,180);
                      drawCanvas();
                      text("Good night!",20,30);  
                      sleeping = 1;
                      noTint();
                    }
                    else
                    {
                      print("Error: invalid UART Sleep == ");       
                      println(buf1);                  
                    }
                    break;    
                    
      case CENTER_BUTTON_CODE:
                   while (buf1 <0)
                      buf1 = LaunchPad.read();      
                   if (buf==buf1)
                   {
                     if (unlocked==1)
                     {
                        unlocked = 0;
                        link(secretURL); 
                     }
                     CenterButtonToggle = 1 - CenterButtonToggle;                     
                     if (CenterButtonToggle == 1)
                     {
                       innerCircleImage= loadImage("innerCircleSelected.png");
                       backgroundImage = loadImage("backgroundSelected.png");
                     }
                     else
                     {
                       innerCircleImage= loadImage("innerCircle.png");
                       backgroundImage = loadImage("background.png");
                     }
                     drawCanvas(); 
                      centerButton = 1;
                   }
                   else
                   {
                      print("Error: invalid CENTER BUTTON code == ");       
                      println(buf1);                  
                   }
                   break;           
                    
                    
      case GESTURE_STOP:
                   while (buf1 <0)
                      buf1 = LaunchPad.read();      

                    if (buf==buf1)
                    {
                      text("Gesture Released",20,30);      
                      gestureStartingPosition = INVALID_WHEEL_POSITION;
                      gestureStoppingPosition = INVALID_WHEEL_POSITION;  
                      gestureDirection = INVALID_GESTURE_DIRECTION;
                      allLit = 0;  
                      codeCheck = 0;
                      codeLevel = 0;
                      //unlocked = 0;
                    }
                    else
                    {
                      print("Error: invalid GESTURE_STOP code == ");       
                      println(buf1);                  
                    }
                    break;         
                    
      case GESTURE_START:
 
                    while (buf1 <0)
                      buf1 = LaunchPad.read();      

                    if ( (buf1 < GESTURE_POSITION_OFFSET ) || (buf1 > GESTURE_POSITION_OFFSET + NUMBER_OF_WHEEL_POSITIONS))
                    {
                      print("Error: invalid gesture start position == ");  
                      println(buf1);
                    }
                    else
                    {                      
                      text("Gesture Detected",20,30);    
                      buf1 = buf1 - GESTURE_POSITION_OFFSET;
                      if (buf1<0)
                        println(buf);
                      gestureStartingPosition = buf1;                      
                      gestureStoppingPosition = buf1;
                      if (buf1 == code[0])
                        codeCheck = 1;
                      else
                        codeCheck = -1;

                      codeLevel = 0;
                      changeDirection = 0;
                      drawSlice(buf1, 1);
                      fill(255);
                      ellipse(CIRCLE_CENTER_X, CIRCLE_CENTER_Y, IN_CIRCLE_RADIUS*2 , IN_CIRCLE_RADIUS*2);  
                      image(innerCircleImage,0,0);
                    }     
                    break;
                                           

      default:    // data from LaunchPad is not code, but value             
      
        if (buf > WHEEL_POSITION_OFFSET + NUMBER_OF_WHEEL_POSITIONS  )         // Invalid Code 
        {
          print("Error: invalid UART code == ");          
          println(buf);
        }
        else                    
        /*---------------------WHEEL POSITION-----------------------*/
        if ((buf <= WHEEL_POSITION_OFFSET + NUMBER_OF_WHEEL_POSITIONS) && (buf >= WHEEL_POSITION_OFFSET )) // Tapping
        {
 
          while (buf1 <0)
            buf1 = LaunchPad.read();            
          if (buf==buf1)
          {
            buf = buf - WHEEL_POSITION_OFFSET;              
            text("Press @ ",10,30);
            text(buf,125,30);         
            tapping = 1;          
            drawSlice(buf, TAP_SLICE_COLOR);
            fill(255);
            ellipse(CIRCLE_CENTER_X, CIRCLE_CENTER_Y, IN_CIRCLE_RADIUS*2 , IN_CIRCLE_RADIUS*2);    
            image(innerCircleImage, 0,0);            
          }
          else
          {
            print("Error: invalid WHEEL POSITION code == ");          
            println(buf);
          }
        }        
        else          
        /*---------------------GESTURE DATA-----------------------*/
        if (buf <  GESTURE_POSITION_OFFSET ) // Gesturing
        if (gestureStartingPosition != INVALID_WHEEL_POSITION)
        {
          if (buf>=NUMBER_OF_WHEEL_POSITIONS)           // Determine orientation: binary value 00000xxx = CW, 00001xxx = CC
          {                                                                                              
            buf -= NUMBER_OF_WHEEL_POSITIONS;
            text(buf, 20,30);
            text("Counter-Clockwise",55,30);        
            gestureImmediateDirection = GESTURE_COUNTERCLOCKWISE;
          }
          else
          {
            text(buf, 20,30);
            text("Clockwise",55,30);        
            gestureImmediateDirection = GESTURE_CLOCKWISE;
          } 

          while (buf1 <0)
            buf1 = LaunchPad.read();      
          if ( (buf1 >= GESTURE_POSITION_OFFSET ) && (buf1 < GESTURE_POSITION_OFFSET + NUMBER_OF_WHEEL_POSITIONS))
          {
            buf1 = buf1 - GESTURE_POSITION_OFFSET;
            if (gestureDirection == INVALID_GESTURE_DIRECTION)
              gestureDirection = gestureImmediateDirection;

            //                                    if (gestureImmediateDirection != gestureDirection)                                    
            //                                          gestureCoverPositions[gestureStoppingPosition] = 0;
            //                                    
            while (buf-->0)
            {
              if (gestureStoppingPosition == gestureStartingPosition) //If moving from the starting position              
                if (gestureDirection != gestureImmediateDirection)  //If moving against the current direction
                {                                                  
                  if (allLit == 0)                                 //Starting at zero? Change direction                 
                    gestureDirection = gestureImmediateDirection;                 
                  else                                            //Back to a previous revolution?                    
                    allLit--;
                }  
              gestureStoppingPosition += gestureImmediateDirection;
              if (gestureStoppingPosition == NUMBER_OF_WHEEL_POSITIONS)
                gestureStoppingPosition = 0;
              if (gestureStoppingPosition < 0)
                gestureStoppingPosition = NUMBER_OF_WHEEL_POSITIONS-1;

              if (gestureStoppingPosition == gestureStartingPosition)  //If moving to the starting position                                    
              {
                if (gestureImmediateDirection == gestureDirection)     //complete a revolution? 
                  allLit += 1;
                else                
                  if (allLit == 0)  //Back to zero                  
                    gestureDirection = INVALID_GESTURE_DIRECTION;                          
                //Undo  
              } 
            }
            
            for ( i = 0; i < NUMBER_OF_WHEEL_POSITIONS; i++)
              gestureCoverPositions[i] = allLit;

            i = gestureStartingPosition;
            while (i != gestureStoppingPosition) 
            {
              gestureCoverPositions[i]= allLit + 1;
              i += gestureDirection;
              if (i<0)
                i = NUMBER_OF_WHEEL_POSITIONS-1;
              if (i == NUMBER_OF_WHEEL_POSITIONS)
                i = 0;
            }                                    
            gestureCoverPositions[i]= allLit + 1;

            for ( i = 0; i < NUMBER_OF_WHEEL_POSITIONS; i++)
              if (gestureCoverPositions[i] > 0)
                drawSlice(i, gestureCoverPositions[i]);
            fill(255);
            ellipse(CIRCLE_CENTER_X, CIRCLE_CENTER_Y, IN_CIRCLE_RADIUS*2 , IN_CIRCLE_RADIUS*2);  
            image(innerCircleImage,0,0);
            
            if (changeDirection !=0)
            {
                if (gestureImmediateDirection != changeDirection)
                  codeCheck = -1;                  

                changeDirection = 0;  
            }
            if (soundEnabled == 1)
              click.play();      
            if (codeModeEnabled == 1)
            {  
              if (codeCheck==1)
              {              
                codeValid = 1;
                for ( i = 0; i < NUMBER_OF_WHEEL_POSITIONS; i++)
                  if (gestureCoverPositions[i] != codeValues[codeLevel][i])
                    codeValid  = 0;
                if (codeRotate[codeLevel] != gestureImmediateDirection)              
                  codeValid = 0;   
                if (codeValid == 1)
                {  
                  if (codeLevel++ < 2) 
                  {
                    changeDirection = -gestureImmediateDirection;
                    if (soundEnabled == 1)
                      clickFound.play();
                  }
                  else
                  {
                    fill(0);
                    text("Unlocked!!",400,30);  
                    text("Press Center",500,90);
                    unlocked = 1;
                    codeLevel = 0;
                    codeCheck = -1;
                    if (soundEnabled == 1)
                      clickOpen.play();
                  }
                }    
              }
            }
          }  
          // invalid gesture data
          else
          {
            print("Error: invalid gesture position data == ");  
            println(buf1);
          }
        }
        else
        { // Should not happen
          buf = buf - GESTURE_POSITION_OFFSET;              
          println("Invalid UART Data, not expecting such data");
        }



        break;
      }

    }   


    else
    {             
       if (++inactivityCounter==TIME_OUT)
       {
         if (sleeping==1)
         {
            goToSleep();
         }
         else
         
           drawCanvas();     
         
       }
      
    }

  }
  
}

void mouseReleased()
{
  if ( (mouseX-CANVAS_SIZE_X/2)*(mouseX-CANVAS_SIZE_X/2) + (mouseY-CANVAS_SIZE_Y/2)*(mouseY-CANVAS_SIZE_Y/2) < IN_CIRCLE_RADIUS * IN_CIRCLE_RADIUS )
    if (LaunchPadComPortFound ==1)
    {
      soundEnabled = 1 - soundEnabled;
      codeModeEnabled = 1 - codeModeEnabled;    
      drawNumberEnabled = 1 - drawNumberEnabled;      
    }

  
}






































/*---------Embedded code validation------------------*/
// Ideally nobody should ever bother scrolling down here
// But good job, you've found it the easy way!
// Anyways, don't spoil the fun for others would ya?
int[] code = { 0, 4, 3, 0};
int[] codeRotate = {1, -1, 1};
int[][] codeValues = { {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                       {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}; 
String secretURL = "http://ti.com/msp430rr";          
int codeCheck, codeLevel, codeValid, changeDirection, unlocked=0, codeModeEnabled = 0;



