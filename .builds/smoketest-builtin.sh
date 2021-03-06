#!/bin/sh

# Devices that exist on sr.ht
if [ -e "/dev/input/event0" ]
then
   file="/dev/input/event0"
elif [ -e "/dev/dri/card0" ]
then
   file="/dev/dri/card0"
else
   echo "No useful device file found"
   exit 1
fi

#
# Run simpletest a few times
#
cnt=0
while [ "$cnt" -lt 5 ]
do
   echo "Simpletest run $cnt"
   if ! sudo LIBSEAT_BACKEND=builtin LIBSEAT_LOGLEVEL=debug SEATD_SOCK=./seatd.sock ./build/simpletest $file
   then
      echo "Simpletest failed"
      exit $res
   fi
   cnt=$((cnt+1))
done

echo "smoketest-builtin completed"
