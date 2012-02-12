#!/bin/bash

./chef -c

function build() {

	echo "Purging $1..."
	test -e $1 && rm -rf $1

}
function docs() {

	echo "Cleaning docs..."
	test -e && rm -rf html

}

test -e MCUS && source MCUS

