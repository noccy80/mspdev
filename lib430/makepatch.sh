#!/bin/bash

echo "This script will create a patch file that can be submitted for inclusion in"
echo "lib430. First you need to give a short name for the patch. This should be"
echo "descriptive, and should only contain lowercase letters and dashes (-)."
echo
echo -n "Patch Description (f.ex. fix-feature-a): "
read descript
./chef -v -a $descript
echo
echo "Please send your patcha via e-mail to cvagnetoft at gmail.com. Make sure to"
echo "include a proper description in full text to describe what your patch does."
