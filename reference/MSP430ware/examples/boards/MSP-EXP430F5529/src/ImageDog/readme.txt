ImageDog v1.00.01

A command line image converter to create C data structures
that can be efficiently processed by DOGS102x-6 displays.

Program by Andreas Dannenberg
(C)2011 Texas Instruments, Inc.

********************************************************************************
Revision History
********************************************************************************
Ver 1.00.01 - May 26th, 2011
- Updated project settings to only require JREv5 to fix compatibility issue
  with the current CCSv4 JRE which is being used. No code changes.
    
Ver 1.00.00 - May 24th, 2011
- Initial Production Release

--------------------------------------------------------------------------------

Folder Contents:

ImageDog---+---.settings/               Eclipse settings folder
           +---.classpath               Eclipse settings file
           +---.project                 Eclipse project file
           +---ImageDog.bat             Convenience script to use the tool
           +---ImageDog.class           Compiled Java code (the executable)
           +---ImageDog.java            Project source code
           +---readme.txt               This file
           
--------------------------------------------------------------------------------

All you really need is the ImageDog.bat file and the ImageDog.class file. The
BAT file is provided as a convenience method to start the converter tool. Note
that the resulting output image will be monochrome with a maximum resolution
of 102x64 pixels. Larger source images can be used however they will get cropped
accordingly.

Usage: ImageDog [-v] file
  file   Input image file in either JPEG, PNG, BMP, or GIF format.
  -v     Cause ImageDog to be verbose, showing various image stats
         and rendering the actual monochrome image to the console.

By default the output will go to the console window. If you want to create a
file you need to re-direct the output using the standard redirection operator.
For example, let’s say you have an image file called myImage.bmp, and you want
to create a C file named output.c containing a C-structure with your image
data, your command line call would look like this:

> imagedog myImage.bmp > output.c

You can also "render" how ImageDog interprets your file directly to the console
window by using the "verbose" option to double-check if the result is what you
like.

> imagedog –v myImage.bmp
