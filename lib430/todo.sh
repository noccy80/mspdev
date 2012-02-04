#!/bin/bash

find . -iname "*.c" > .todocache
find . -iname "*.h" >> .todocache
find . -iname "*.cpp" >> .todocache

for file in `cat .todocache`; do

	cat "$file" | grep -i "TODO" > .todotmp
	if [ "$?" == "0" ]; then
		printf "%s:\n" $file
		cat .todotmp
		rm .todotmp
	fi
done
