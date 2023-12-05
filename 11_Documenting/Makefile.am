SUBDIRS = src po

# https://git.sr.ht/~frbrgeorge/namegen/tree/master/item/Makefile.am
@DX_RULES@

doxygen-doc/man/man3/guess.c.3: doxygen-doc

man1: bin/guess
	help2man bin/guess > man1

man1_MANS = doxygen-doc/man/man3/guess.c.3 man1

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

http:	doxygen-doc
	python3 -m http.server --directory $</html

clean:
	git clean -Xf
	rm -rf src/*.o src/.deps/ m4/ autom4te.cache/
