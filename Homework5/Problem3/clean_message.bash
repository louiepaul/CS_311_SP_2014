#!/bin/sh
# remove semaphores
IDS=`ipcs -s | grep $LOGNAME| awk '{print $2}'`
for i in $IDS ; do ipcrm sem $i ; done
# remove shared memory
IDS=`ipcs -m | grep $LOGNAME| awk '{print $2}'`
for i in $IDS ; do ipcrm shm $i; done
# remove message queues
IDS=`ipcs -q | grep $LOGNAME| awk '{print $2}'`
for i in $IDS ; do ipcrm msg $i; done
