#!/bin/bash
tar -xf input.tar.gz	# extract tar.gz file

mkdir TXT

find . -name "*.txt" -print0  | xargs -0 -I {} mv {} TXT/  # move all txt files into TXT

mkdir JPG

find . -name "*.jpg" -print0  | xargs -0 -I {} mv {} JPG/ # move all jpg files into JPG

mkdir ZIP

mv input/* ZIP/		# move rest files intp ZIP

# Create zip file and zip it
mv ZIP/ rest_zipped/	

tar czf rest_zipped.tar.gz rest_zipped/

