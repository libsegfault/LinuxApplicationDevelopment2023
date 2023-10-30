CC = gcc
	CFLAGS = -Wall -Werror -g -fPIC

all: move
move: move.c
	$(CC) $(CFLAGS) -o $@ $<

libprotect.so: libprotect.c
	$(CC) -shared $< -o $@

test: move libprotect.so
	@echo Running tests...
	@./test.sh 1 openat EPERM 3 2 in
	@./test.sh 2 openat EPERM 4 3 in
	@./test.sh 3 read EINTR 2 6 in
	@./test.sh 4 close EINTR 3 8 in
	@echo TEST5 > PROTECTED
	@LD_PRELOAD=./libprotect.so ./move PROTECTED out 1> /dev/null
	@test -f PROTECTED && test -f out || echo Test 5 failed!
	@echo Done!

clean:
	rm -rf move libprotect.so in out PROTECTED
