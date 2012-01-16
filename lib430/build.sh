#!/bin/bash

OP=""
while getopts ":m:vhbrlp" opt; do
	case $opt in
		m)
			MCU="$OPTARG"
			;;
		p)
			OP="package"
			;;
		l)
			OP="list"
			;;
		r)
			OP="remove"
			;;
		b)
			OP="build"
			;;
		v)
			;;
		h)
			echo "`basename $0` - Repair Chromium when it goes all lockout on you"
			echo "(c) 2011-2012, Noccy.com"
			echo
			echo "Usage: `basename $0` [-m <mcu>] [-v] -b"
			echo "       `basename $0` [-m <mcu>] -r"
			echo "       `basename $0` -l"
			echo "       `basename $0` -h"
			echo ""
			echo "  -m  MCU (msp430g2553,...)"
			echo "  -p  Package module"
			echo "  -r  Remove modules"
			echo "  -l  List modules"
			echo "  -h  Show this help"
			exit 1
			;;
	esac
done

case "$OP" in
	"list")
		ls -al msp430*
		;;
	"build")
		if [ -z "$MCU" ]; then
			echo "No MCU defined. Either export MCU or use -m MCU."
			exit 1
		fi
		rm -rf $MCU
		mkdir -p $MCU/include $MCU/lib

		LIBS="libcomm libcore libhal libgpio libair libmidi liblcd"
		for LIB in $LIBS; do
			echo "Building $LIB"
			cd src/$LIB
			if [ -e Makefile ]; then
				echo " - Building"
				make clean &> /dev/null && make lib &>../../$MCU/$LIB.log
			fi
			echo " - Installing"
			cp $LIB.a ../../$MCU/lib/ &>/dev/null
			cp *.h ../../$MCU/include/ &>/dev/null
			cd ../..
		done
		echo "Chmodding"
		echo " - Libraries"
		chmod 666 $MCU/lib/*.a
		echo " - Includes"
		chmod 666 $MCU/include/*.h
		;;
	"package")
		if [ ! -d "$MCU" ]; then
			echo "You need to build it first..."
			exit 1
		fi
		tar cvfz lib430-$MCU.tgz $MCU
		;;
	*)
		echo "Try -h"
		;;
esac

