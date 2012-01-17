#!/bin/bash
LIBS="libcomm libcore libhal libgpio libair libmidi liblcd libarduino"
OP=""
while getopts ":m:vhbrlcp" opt; do
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
		c)
			OP="clean"
			;;
		v)
			;;
		h)
			echo "`basename $0` - lib430 Builder"
			echo "(c) 2011-2012, NoccyLabs.info"
			echo
			echo "Usage: `basename $0` [-m <mcu>] [-v] -b"
			echo "       `basename $0` [-m <mcu>] -r"
			echo "       `basename $0` -l"
			echo "       `basename $0` -c"
			echo "       `basename $0` -h"
			echo ""
			echo "  -m  MCU (msp430g2553,...)"
			echo "  -p  Package module"
			echo "  -r  Remove modules"
			echo "  -l  List modules"
			echo "  -c  Clean modules"
			echo "  -h  Show this help"
			exit 1
			;;
	esac
done

case "$OP" in
	"list")
		ls -al | grep msp430*
		;;
	"clean")
		for LIB in $LIBS; do
			echo -n " :: $LIB: "
			cd src/$LIB
			if [ -e Makefile ]; then
				make clean &> /dev/null
			fi
			echo "Clean"
			cd ../..
		done
		;;
	"build")
		if [ -z "$MCU" ]; then
			echo "No MCU defined. Either export MCU or use -m MCU."
			exit 1
		fi
		echo "Building for $MCU ..."
		rm -rf $MCU
		mkdir -p $MCU/include $MCU/lib

		for LIB in $LIBS; do
			echo -n " :: $LIB: "
			cd src/$LIB
			if [ -e Makefile ]; then
				make clean &> /dev/null
				make lib &>../../$MCU/$LIB.log
			fi
			echo "Installing"
			cp $LIB.a ../../$MCU/lib/ &>/dev/null
			cp *.h ../../$MCU/include/ &>/dev/null
			cd ../..
		done
		chmod 666 $MCU/lib/*.a
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

