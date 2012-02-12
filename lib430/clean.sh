#!/bin/bash

./chef -c

function build() {

	rm -rf $1

}
function docs() {

	rm -rf html

}

test -e MCUS && source MCUS

