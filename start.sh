#!/bin/bash

function get_distro() {
	echo -n "Determining distribution ... "
	DISTRO="linux/unknown"
	uname -v | grep -i ubuntu &>/dev/null && DISTRO="linux/debian"
	uname -v | grep -i debian &>/dev/null && DISTRO="linux/debian"
}

get_distro

echo "`basename $0` ($DISTRO)"
echo
echo "Hello, and welcome to the mspdev quickstarter!"
echo
echo "This script will get everything going for you in just a few short steps."
echo
echo "You will be prompted for each step. Answer the question with a lowercase 'y' to"
echo "complete the specified step. Any other key will skip it."
echo

echo
echo "== CLEAN EVERYTHING =========================================================="
echo
echo "   This will clear all temporary build files."
echo
echo -n "   Clean everything [y/n]? "
read ans
if [ "$ans" == "y" ]; then
	echo "   Building..."
	pushd lib430; ./clean.sh; popd
	pushd examples/blink; make clean; popd
	pushd examples/libarduino; make clean; popd
	pushd examples/blink; make clean; popd
	echo 'All done!'
fi
echo

if [ "`which msp430-gcc`" == "" ]; then
echo
echo "== INSTALL MSP430-GCC AND MSPDEBUG ==========================================="
echo
echo "   This is the environmen, msp430-gcc. This needs for you to have downthemall"
echo "   for php installed, which in turn depends on lepton. Saying y here is likely"
echo "   to fail."
echo
echo -n "   Install helpers [y/n]? "
read ans
if [ "$ans" == "y" ]; then
	case "$DISTRO" in
	"linux/debian")
		echo "   Downloading msp430-gcc into tools/.cache ..."
		pushd tools
		ARCH="`uname -i`"
		test -d .cache || mkdir .cache
		cd .cache
		curl -o mspdev-$ARCH.tgz "http://files.noccylabs.info/mspdev-$ARCH.tgz"
		cd ..
		sudo apt-get -y install mspdebug
		sudo dpkg -i .cache/$ARCH/binutils-msp430_*.deb .cache/$ARCH/gcc-msp430_*-1_*.deb .cache/$ARCH/gdb-msp430_*.deb .cache/$ARCH/msp430-libc_*.deb
		sudo apt-get -f install
		popd
		;;
	"unknown")
		echo "Sorry, unknown platform"
		;;
	esac
fi
fi

echo
echo "== INSTALL HELPERS ==========================================================="
echo
echo "   The helpers consist of:"
echo "    - msp430-comm - quick serial comm setup thingie"
echo "    - msp430-findfeat - find devices with specific features"
echo "    - msp430-identify - outputs the mcu type of the attached device"
echo
echo -n "   Install helpers [y/n]? "
read ans
if [ "$ans" == "y" ]; then
	echo "   Installing..."
	if [ ! -d "~/bin" ]; then
		mkdir -p ~/bin
		export PATH="~/bin:$PATH"
	fi
	for bin in msp430-comm msp430-findfeat msp430-identify; do
		rm -rf ~/bin/$bin
		cp ./tools/$bin ~/bin/$bin
	done
fi

echo
echo "== BUILD LIB430 =============================================================="
echo
echo "   This will build lib430 for the devices listed in the MCUS file. if this file"
echo "   does not exist, it will be created from the MCUS.example file. This is a good"
echo "   thing to do. Just remember to rebuild it with the buildall.sh script when the"
echo "   source has been updated."
echo
echo -n "   Build lib430 [y/n]? "
read ans
if [ "$ans" == "y" ]; then
	if [ ! -e "lib430/MCUS" ]; then
		echo "   Installing MCUS.example as MCUS..."
		cp lib430/MCUS.example lib430/MCUS
	fi
	echo "   Building..."
	pushd lib430
	./buildall.sh
	popd
fi
echo

echo
echo "== BUILD EXAMPLES ============================================================"
echo
echo "   This will build the examples for the microcontroller that is attached on the"
echo "   launchpad via usb. It will then program the blink example onto the device."
echo
echo '   MAKE SURE THAT YOUR LAUNCHPAD IS ATTACHED BEFORE CONTINUING!'
echo
echo -n "   Build examples [y/n]? "
read ans
if [ "$ans" == "y" ]; then
	echo "   Building..."
	pushd examples/blink; make bin; popd
	pushd examples/libarduino; make bin; popd

	pushd examples/blink; make prog; popd
echo 'All done!'
fi
echo
