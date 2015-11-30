# liblistmisc
A very small, very simple implementation of a  linked list for C.

## Please note:
* I wrote this library since all the other list implementations I found were hard to understand and/or had tons of features that I don't need.
* You most like do not want to use this library in a productive environment.
* However, it will hopefully help you to prototype some small software or understand linked lists.

# Compiling:
Simply type:

    make

This will produce a shared library, called "liblistmisc.so", which you can link to your software.

Since the *liblistmisc* is so small, you might prefer a static library:

    make static

To produce debug versions of the *liblistmisc*:

    make shared-debug      # Shared library with debugging symbols
    make static-debug      # Static library with debugging symbols


# Installation (optional):
Use:

    make install

This will copy the *liblistmisc.so* to /usr/local/lib and the header *listmisc.h* to /usr/local/include; nothing fancy here.

# Small example:
    #include <stdio.h>
    #include <string.h>

    #include "listmisc.h"

    int main() {
        // Create a new, empty list.
        list_t *list = list_create();

        // Fill the list with some strings
        list_add(list, strdup("Item 1"));
        list_add(list, strdup("Item 2"));
        list_add(list, strdup("Item 3"));

        // Iterate over all items in the list.
        // Note: C99 support is required for the list_foreach macro.
        list_foreach(list, it) {
                char *data = (char*)it->d;
                printf("%s\n", data);
        }

        // Free all memory. Note that list_free also frees every data element.
        list_free(list);

        return 0;
    }

Compile with:

    gcc -std=c99 example.c liblistmisc.a -o example -D_GNU_SOURCE

# Platform support:
The *liblistmisc* has been successfully compiled and run using gcc, clang and even MSVC. The MSVC support has not been tested extensively, so don't expect miracles.


----
## Todo
* Provide more documentation.

