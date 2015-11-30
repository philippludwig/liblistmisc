#include <stdlib.h>
#include <stdio.h>

#include "list.h"

int list_add(list_t *list, void *data)
{
	// Valid list?
	if(!list) {
		printf("%s","[WARN] list_add: list == 0\n");
		return 0;
	}

	// Create new node.
	list_t *node = calloc(1, sizeof(list_t));
	node->d = data;

	// Add node.
	list->end->next = node;
	list->end = node;

	// Success.
	return 1;
}

void* list_remove(list_t *list, const void *data)
{
	if(!list || !data) return 0;

	// Find the corresponding list element.
	struct list_t *prev = list;
	for(list_t *it = list_start(list); it != NULL; it = it->next) {
		if(it->d != data) {
			prev = it;
			continue;
		}

		// Remove the element.
		prev->next  = it->next;
		void *ret = it->d;

		// Update the end pointer if needed.
		if(list->end == it) list->end = prev;

		free(it);
		return ret;
	}

	return 0;
}

list_t* list_start(const list_t *list)
{
	if(!list) return 0;
	return list->next;
}

list_t* list_create()
{
	list_t *list = calloc(1, sizeof(list_t));
	if(!list) return 0;
	list->end = list;
	return list;
}

char list_empty(const list_t *list)
{
	if(!list) return 1;
	if(!list->next) return 1;
	return 0;
}

void list_free(list_t *list)
{
	for(list_t *it = list; it != 0; ) {
		if(it->d) free(it->d);
		it->d = 0;

		list_t *tmp = it;
		it = it->next;
		free(tmp);
	}
}
