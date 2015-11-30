#ifndef LIST_H_
#define LIST_H_

/** List structure. **/
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
 * @return 1: success, 0: failure.
 */
int list_add(list_t *list, void *data);

/** Return the beginning of the list. **/
list_t* list_start(const list_t *list);

/** Return 1 if the given list is empty. **/
char list_empty(const list_t *list);

/** Remove the given data from the given list. **/
void* list_remove(list_t *list, const void *data);

#if (__STDC_VERSION__ >= 199901L) || (_MSC_VER >= 1800)
#define list_foreach(list,it) for(list_t *it=list_start(list);it!=NULL;it=it->next)
#endif

#endif /* LIST_H_ */
