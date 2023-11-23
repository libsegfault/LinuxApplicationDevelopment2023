all: patch maze-v0 maze-v1 maze-v2 maze-v3

patch:
	patch -o maze-v1.c -i 0001-PatchDiff-Configurable-size.patch
	patch -o maze-v2.c -i 0002-PatchDiff-Configurable-wall-and-empty-space-chars.patch
	patch -o maze-v3.c -i 0003-PatchDiff-Configurable-random-number-generator-seed.patch

maze-v%: maze-v%.c

run: all
	./maze-v0
	./maze-v1 7
	./maze-v2 ' 0' 8
	./maze-v3 666 ' #' 9

clean:
	rm -rf maze-v[0-3] maze-v[1-3].c
