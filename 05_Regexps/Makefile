esub: esub.c
	gcc -O0 -g -o $@ $^


test: esub
	./esub "regexp" "substitution" "some string with regexp and regexp" > test1.txt
	echo some string with regexp and regexp | sed -E 's/regexp/substitution/' > ref1.txt
	./esub '^(0+)1' \1 0000000000011111 > test2.txt
	echo 0000000000011111 | sed -E s/^\(0+\)1/\1/ > ref2.txt
	cmp test1.txt ref1.txt
	cmp test2.txt ref2.txt
	@echo All tests passed successfully!
clean:
	rm -f esub test*.txt ref*.txt
