#!/bin/bash
echo "TEST$1" > $6
strace -e fault=$2:error=$3:when=$4 ./move $6 out > /dev/null 2>&1
test $? -eq $5 && test -f in || echo "Test $1 failed."
rm -f in out
