#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>

static int (*real_rename)(const char *old, const char *new) = 0;

int rename(const char *old, const char *new) {
    char* message;
    
    if (!real_rename) {
        real_rename = dlsym(RTLD_NEXT, "rename");
    
        if ((message = dlerror()) != NULL) {
            printf(" *** rename dlopen failed: %s\n", message);
        }
    }
    printf(" -- Spotted moving %s to %s\n", old, new);
    
    return real_rename(old, new);
}

