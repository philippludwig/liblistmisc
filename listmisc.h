#ifndef LIST_H_
#define LIST_H_

/* liblistmisc header file 
 *
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
 **/

// This header is just included for the return type for some methods.
// If you prefer do use as little standard library features as possible,
// just #define bool, true and false yourself.
#include <stdbool.h>

#ifndef NULL
#define NULL 0
#endif

/**
 * @brief List structure.
 *
 * This is the structure of a list node.
 * next points to the next list item, end points always to the last
 * item in the list.
 * d points to the data item transferred with list_add.
 *
 * Please note that the very first item of every list is not
 * a valid list node, that means it does not hold any data.
 *
 * This approach was chosen to allow "empty" lists.
 *
 * Refer to the file "example.c" or "README.md" for usage instructions.
 **/
typedef struct list_t {
	/** Data that this node contains, can be anything. **/
	void *d;

	/** Next node. **/
	struct list_t *next;

	/** Last node. **/
	struct list_t *end;
} list_t;

/** Create a new empty list. **/
list_t* list_create();

/** Free the given list (including all elements). **/
void list_free(list_t *list);

/**
 * @brief Add some data to the given list.
 * @param list A pointer to a list_t element.
 * @param data A pointer to the data that will be hold by the new list element.
 *
 * Note: The ownership of the pointer is transferred to the new list item.
 * Therefore, data must not be freed after list_add has been called.
 *
 * If you want to free the data after it has been added to the list,
 * call list_remove first!
 *
 * @sa list_remove
 * @return true: success, false: failure.
 */
bool list_add(list_t *list, void *data);

/** Return the beginning of the list. **/
list_t* list_start(const list_t *list);

/** Return true if the given list is empty. **/
bool list_empty(const list_t *list);

/** 
 * @brief Remove the given data from the given list. 
 * @return A pointer to data that has been removed. 
 ***/
void* list_remove(list_t *list, const void *data);

// The list_foreach macro depends on C99 support / recent versions of MSVC.
#if (__STDC_VERSION__ >= 199901L) || (_MSC_VER >= 1800)
/**
 * @brief Handy macro which makes it easier to iterate over a list.
 */
#define list_foreach(list,it) for(list_t *it=list_start(list);it!=NULL;it=it->next)
#endif

#endif /* LIST_H_ */
