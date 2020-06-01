#!bin/bash

mkdir Assignment-1 # make directory Assignment-1
cd Assignment-1


for i in {1..10} # do the following tasks
do
	mkdir Query-$i
	cd Query-$i
	touch response-$i.sh
	cd ..
done

