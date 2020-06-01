#!/bin/bash 


rm -f infloop  pids.log
gcc iloop.c -o infloop 

counter=1
while [ $counter -le 10 ]
do
	./infloop&
	counter=$[$counter+1] 
done

echo "finished spawning 10  processes"  

# record child pids
mypid=$(echo $$)
ppids=$(pgrep -P $mypid)
echo ${ppids} > pids.log


#ppids=$(pidof ./infloop)
#ppids=$(pstree -p $mypid)
