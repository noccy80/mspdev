#!/bin/bash
if [ ! -e MCUS ]; then
	echo "For the BuildAll script to work, you need to create a file named MCUS"
	echo "in the same folder, and populate it with the keyword 'build' followed"
	echo "by a the mcu and any defines, for example:"
	echo ""
	echo '  build msp430g2553 "-DWITH_HUART=1 -DUPTIME_USE_WDT"'
	echo ""
	exit 1
fi
function build() {

	if [ "$2" == "" ]; then
		export CXXFLAGS=""
	else
		export CXXFLAGS="$2"
	fi
	./chef -m $1 -b

}

source MCUS

