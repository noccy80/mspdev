#!/bin/bash
if [ ! -e MCUS ]; then
	cp MCUS.example MCUS
	if [ "`which editor`" == "" ]; then
		echo "I have created MCUS for you, but you need to edit it yourself."
		echo "Then re-run this script."
		exit 1
	else
		editor MCUS
		$0
	fi
fi
function libraries() {
	export LIBRARIES="$1"
}
function build() {

	if [ "$2" == "" ]; then
		export CXXFLAGS=""
	else
		export CXXFLAGS="$2"
	fi
	export DEST="`dirname $0`/$MCU"
	export LIB430LIBS="$LIBRARIES $3"
	./chef -m $1 -b

}
function docs() {

	./chef -D

}

source MCUS

