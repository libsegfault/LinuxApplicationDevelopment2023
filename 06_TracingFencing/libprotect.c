#include <stdio.h>
#include <dlfcn.h>
#include <string.h>


int remove(const char * pathname) {
    if (strstr(pathname, "PROTECT") == NULL) {
        int (*real_remove)() = dlsym(RTLD_NEXT, "remove");
        if (!real_remove) {
            return -1;
        }
        return real_remove(pathname);
    }
    return 0;
}
