# lib430: A FLOSS framework for the MSP430 Series microcontrollers

-------------------------------------------------------------------------------

## Components

### libarduino

Provides an arduino-esque platform, implementing most of the arduino API
functions. Linking with this library, you don't have to worry about setting
up a `main()` function - just do the usual `setup()` and `loop()`.

[Read More...](src/libarduino/README "libarduino")

### libair

Interface with wireless devices using the _Anaren AIR Platform_ or using the
lighter _NiNet_. You know, _the Net who says Ni._ Communication can be done
over a _TI CC1101_ sub-1ghz wireless radio, or a _RFM70_ 2.4ghz radio.

[Read More...](src/libair/README "libair")

### libcomm

Unifies everything communication. Fifo buffers, SPI, I2C, UART, HUART, SUART
and just about any other communications term you can imagine.

[Read more...](src/libcomm/README "libcomm")

### libhal

Abstracts the hardware for you, so you don't have to. Shoves the most commonly
used bits and bobs into structures that can be passed around in a simple
and effective manner.

[Read more...](src/libhal/README "libhal")

### libmidi

This is a MIDI implementation, that allows your device to become either a host
or a slave in a MIDI network. Build yourself a MIDI-powered mixer panel, or
just hook up some knobs and build yourself a synthesizer.

[Read more...](src/libmidi/README "libmidi")

### And more ...

This document is still being written.

## Using
 
To use it you need to build it. Do this with the build.sh script which will 
take care of the rest for you. All the libraries will be built for the desired
microcontroller and furthermore copied into the appropriate folders.

The way this is done is by creating a subdirectory in the lib and include
folders named by the microcontroller. So, when building your project, you
simply pass -Ilib430/msp430g2553/include -Llib430/msp430g2553/lib as the
custom library path.

Some projects that use lib430:

 * [msPOV Persistence of Vision Display](/mspdev/projects/mspov/README "README for msPOV")
 * [Blink - Simple LED blinker](/mspdev/projects/blink/README "README for Blink")
 * [RGBlink - A RGB blinker](/mspdev/projects/rgblink/README "README for RGBlink")
 * [MIDIPAD - A control surface for MIDI gadgets](/mspdev/projects/midipad/README "README for MIDIPAD")
 
### Status

Currently not all libraries compile for all devices. This is being worked on,
so please consider the current code a work in progress. Contributions are
welcome, see the section "patches" further down this document.
  
## Building

    ./chef -m msp430g2553

Alternatively you can make use of the buildall.sh script:

    ./buildall.sh

Feel free to tweak the MCUS file to contain the controllers you work with.

### Removing builds

    ./chef -m msp430g2553 -r

### Listing installed builds

    ./chef -l

### There is more

    ./chef -h

## Patches
 
Patches are accepted via e-mail to lib430@groups.google.com as long as
they can be applied to the current trunk. They should be performed from the
lib430 root folder:
 
	./chef -a "describe-your-patch" 
 
## Copying/Distributin
 
Released under GNU GPL Version 3.
