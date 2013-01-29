#!/bin/bash -login
# Run BLCR Test from the command line.  

if [ "$1" == "" ]
then
	export test="dynamic"
else
	export test="static"
fi 

echo "Running test $test"

export LANG=C
rm -f context*
ulimit -s unlimited

echo "RUNNING TEST"  
cr_run ./blcr_${test}_test.exe &
export PID=$!

sleep 30
cat /proc/$PID/maps > mem1.txt
echo "Checkpoint"
cr_checkpoint --term ${PID}

sleep 10
echo "Restart"
cr_restart --restore-pid context.${PID} &
export PID=$!
cat /proc/$PID/maps > mem2.txt
rm still_running

(sleep 60; exit 1) &
sleep 70
echo "Complete"


