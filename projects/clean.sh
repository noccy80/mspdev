#!/bin/bash
for F in *; do 
	if [ -d $F ]; then
		cd $F
		make clean 2>/dev/null
		cd ..
	fi
done
