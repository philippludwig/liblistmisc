// Compile me with: gcc -std=c99 example.c liblistmisc.a -o example -D_GNU_SOURCE
// (_GNU_SOURCE is only needed for strdup)

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
