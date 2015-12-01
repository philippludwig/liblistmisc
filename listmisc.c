/* liblistmisc source file.
 *
 * Copyright (c) 2013-2015 Philipp Ludwig <git@philippludwig.net>
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "listmisc.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool list_add(list_t *list, void *data)
{
	// Valid list?
	if(!list) {
		printf("%s","[WARN] list_add: list == 0\n");
		return false;
	}

	// Create new node.
	list_t *node = calloc(1, sizeof(list_t));

	// Assign the data.
	node->d = data;

	// Add node.
	// We do this by updating the next pointer of the last node
	// to point to the newly created node.
	list->end->next = node;

	// Furthermore we update the end pointer of the list item.
	// TODO: Maybe we should update the end pointer of every list item.
	// This could by handled by setting node->prev->end = node,
	// but this hasn't been tested yet.
	list->end = node;

	// Success.
	return true;
}

void* list_remove(list_t *list, const void *data)
{
	// Check for a valid list first.
	if(!list) return 0;

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

		// Free the memory assigned to the removed node.
		free(it);

		// Return the pointer to the data.
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
	// Allocate memory for the new list.
	list_t *list = calloc(1, sizeof(list_t));

	// Return 0 if the memory could not be allocated.
	if(!list) return 0;

	// Initialize the end pointer.
	list->end = list;

	// Return the new created list.
	return list;
}

bool list_empty(const list_t *list)
{
	// Invalid lists are empty lists.
	if(!list) return true;

	// Lists without a next node are empty list-
	if(!list->next) return true;

	// In other cases this list is not empty.
	return false;
}

void list_free(list_t *list)
{
	// Iterate over all items in the list.
	for(list_t *it = list; it != 0; ) {
		// If the data pointer is not a nullptr, we free it.
		if(it->d != 0) free(it->d);
		it->d = 0;

		// We free this node and set our iterator to the next item.
		list_t *tmp = it;
		it = it->next;
		free(tmp);
	}
}

