BIN=prog prog-a prog-so liboutput_static.a liboutput.so
TESTS=prog.0.out prog-a.0.out prog-so.0.out prog.1.out prog-a.1.out prog-so.1.out prog.3.out prog-a.3.out prog-so.3.out

CFLAGS+=-L. -fPIC

all: $(BIN)
fun.o: outlib.h

prog: const.o fun.o prog.o

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^
liboutput.so: fun.o const.o
	$(CC) $(CFLAGS) -shared $^ -o $@

prog-a: prog.o liboutput_static.a
	$(CC) $(CFLAGS) -o $@ $^

prog-so: prog.o liboutput.so
	$(CC) $(CFLAGS) -o $@ $< -loutput

test: $(TESTS)
	@echo "Testing..."
	cmp prog.0.out prog-a.0.out
	cmp prog-a.0.out prog-so.0.out
	cmp prog.1.out prog-a.1.out
	cmp prog-a.1.out prog-so.1.out
	cmp prog.3.out prog-a.3.out
	cmp prog-a.3.out prog-so.3.out

%.0.out: %
	LD_LIBRARY_PATH=. ./$^ > $@ 2>&1
%.1.out: %
	LD_LIBRARY_PATH=. ./$^ 42 > $@ 2>&1
%.3.out: %
	LD_LIBRARY_PATH=. ./$^ 42 test 666 > $@ 2>&1

clean:
	rm -rf *.o $(BIN) $(TESTS)
