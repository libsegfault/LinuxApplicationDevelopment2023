range: range.c
	gcc -O0 -g -o $@ $^

%.txt: %.gdb range
	gdb --batch --quiet -x $^ | grep "@@@" > $@
test: test1.txt test2.txt
	cmp test1.txt ref1.txt
	cmp test2.txt ref2.txt
	@echo All tests passed successfully!
clean:
	rm -f range test*.txt
