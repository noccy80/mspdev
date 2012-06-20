# PCD8544-driver for msp430

This is a complete driver for the Philips PCD8544 LCD driver, used
in the Nokia 3310 displays and subsequently in Olimex MOD-LCD3310
LCD extension.

Expected port/pin mappings:

  - D/_C on P2.0
  - SDIN on P2.1
  - SCE  on P2.2
  - SCK  on P2.3
  - RES  on P2.4

If the display on your device is offset by 5 pixels, causing the
top row of the display to be 5 pixels down, then add the define
`PCD8544_FIX_YALIGN` to your project or `-DPCD8544_FIX_YALIGN` to your
compiler flags in the makefile to fix this problem.

Based on code by TopHatHacker (github.com/tophathacker) and rewritten
and commented for tidyness and modularity.

_Licensed under GNU GPL version 3_
