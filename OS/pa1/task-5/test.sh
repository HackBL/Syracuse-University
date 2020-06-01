#!bin/bash

FILES="sample_data/*"

for f in $FILES	# call each file in subdirectory
do
	filename="$(ls $f | xargs -L 1 basename)"
	count="$(grep -c "smart" $f)"
	printf "%s smart %d\n" $filename $count  
done > result.txt

for f in $FILES # call each file in subdirectory
do
        filename="$(ls $f | xargs -L 1 basename)"
        count="$(grep -c "operating system" $f)"
        printf "%s operating system %d\n" $filename $count
done >> result.txt

mkdir smart
mkdir OS
sleep(1)

for f in $FILES
do 
	if grep -q "smart" "$f"	# find files contains "smart"
	then
		cp $f smart/

	elif grep -q "operating system" "$f" # find files contains "operating system"
        then
                cp $f OS/
        fi
done
