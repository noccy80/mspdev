#!/bin/bash
if [ ! -e MCUS ]; then
	echo "You must first create a file named MCUS and populate it with one microcontroller per line"
	exit 1
fi
for f in `cat MCUS`; do ./build.sh -m $f -b; done
