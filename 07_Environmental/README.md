## Build
```console
autoreconf --install && aclocal && automake --gnu --add-missing && autoconf
./configure [--disable-readline]
make
```
