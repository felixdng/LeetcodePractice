#ifndef __LISTDEMO_H__
#define __LISTDEMO_H__

#include "list.h"

typedef struct listnode {
	slist_t list;
	long long int val;
} listnode_t;

#define TO_SLIST(_listnode) ((slist_t *)(_listnode))
#define TO_LISTNODE(_slist) ((listnode_t *)(_slist))
#define TO_LISTNODE_VAL(_slist) (TO_LISTNODE(_slist)->val)

#ifdef __cplusplus
extern "C" {
#endif

slist_t * demo_list_create(const char *str, slist_t *lh);
void demo_list_destroy(slist_t *lh);
void demo_list_print(slist_t *lh);
slist_t * demo_list_node_new(long long int val, slist_t *next);
slist_t * demo_list_node_new_tail(long long int val, slist_t *prev);

#ifdef __cplusplus
}
#endif

#endif /* __LISTDEMO_H__ */
