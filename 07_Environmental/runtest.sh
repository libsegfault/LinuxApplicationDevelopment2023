#!/bin/bash

ref=$(echo -n TEST1 | sha1sum | cut -f 1 -d ' ')
out=$(echo -n 'SHA1 "TEST1' | ./rhasher | head -n 1 | cut -f 4 -d ' ')
[ "$ref" = "$out" ] || echo "Test 1 failed"

ref=$(sha1sum configure.ac | cut -f 1 -d ' ')
out=$(echo -n 'SHA1 configure.ac' | ./rhasher | head -n 1 | cut -f 4 -d ' ')
[ "$ref" = "$out" ] || echo "Test 2 failed"

ref=$(echo -n TEST3 | md5sum | cut -f 1 -d ' ')
out=$(echo -n 'MD5 "TEST3' | ./rhasher | head -n 1 | cut -f 4 -d ' ')
[ "$ref" = "$out" ] || echo "Test 3 failed"

ref=$(md5sum Makefile.am | cut -f 1 -d ' ')
out=$(echo -n 'MD5 Makefile.am'  | ./rhasher | head -n 1 | cut -f 4 -d ' ')
[ "$ref" = "$out" ] || echo "Test 4 failed"

echo "Testing done"
