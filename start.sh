#!/bin/bash

echo "Hello, and welcome to the mspdev quickstarter!"
echo
echo "This script will get everything going for you in just a few short steps."
echo
echo "You will be prompted for each step. Answer the question with a lowercase 'y' to"
echo "complete the specified step. Any other key will skip it."
echo

echo
echo "1. INSTALL MSP430-GCC"
echo
echo "   This is the environmen, msp430-gcc. This needs for you to have downthemall"
echo "   for php installed, which in turn depends on lepton. Saying y here is likely"
echo "   to fail."
echo
echo -n "   Install helpers [y/n]? "
read ans
if [ "$ans" == "y" ]; then
	echo "   Downloading msp430-gcc into tools/.cache ..."
	pushd tools
	./msp430-install
	popd
fi

echo
echo "2. INSTALL HELPERS"
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
		mkdir ~/bin
		export PATH="~/bin:$PATH"
	fi
	for bin in msp430-comm msp430-findfeat msp430-identify; do
		ln -s ./tools/$bin ~/bin/$bin
	done
fi

echo
echo "3. BUILD LIB430"
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
echo "4. BUILD EXAMPLES"
echo
echo "   This will build the examples for the microcontroller that is attached on the"
echo "   launchpad via usb. It will then program the blink example onto the device."
echo
echo -n "   Build examples [y/n]? "
read ans
if [ "$ans" == "y" ]; then
	echo "   Building..."
	pushd examples/blink; make; popd
fi
echo
echo 'All done!'
