#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>

typedef struct slist {
	struct slist *next;
} slist_t;

#ifdef __cplusplus
extern "C" {
#endif

#define SLIST_HEAD(name) \
	slist_t name = { NULL }

static inline void INIT_SLIST_HEAD(slist_t *list)
{
	list->next = NULL;
}

static inline void __slist_add(slist_t *entry, slist_t *prev)
{
	entry->next = prev->next;
	prev->next = entry;
}

static inline slist_t *__slist_tail(slist_t *head)
{
	slist_t *tail = head;
	while (NULL != tail->next)
		tail = tail->next;
	return tail;
}

static inline slist_t *__slist_prev(slist_t *entry, slist_t *head)
{
	slist_t *prev = head;
	slist_t *pos = head->next;
	while (NULL != pos && NULL != pos->next) {
		if (entry == pos)
			break;
		prev = pos;
		pos = pos->next;
	}
	return prev;
}

static inline void slist_add(slist_t *entry, slist_t *head)
{
	return __slist_add(entry, head);
}

static inline void slist_add_tail(slist_t *entry, slist_t *head)
{
	return __slist_add(entry, __slist_tail(head));
}

static inline void __slist_del(slist_t *entry, slist_t *prev)
{
	prev->next = entry->next;
}

static inline void slist_del(slist_t *entry, slist_t *head)
{
	__slist_del(entry, __slist_prev(entry, head));
	entry->next = NULL;
}

static inline void slist_move(slist_t *entry, slist_t *old_h, slist_t *new_h)
{
	slist_del(entry, old_h);
	slist_add(entry, new_h);
}

static inline void slist_move_tail(slist_t *entry, slist_t *old_h, slist_t *new_h)
{
	slist_del(entry, old_h);
	slist_add_tail(entry, new_h);
}

#define slist_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos ? pos->next : NULL; NULL != pos; pos = n, n = pos ? pos->next : NULL)

#ifdef __cplusplus
}
#endif

#endif /* __LIST_H__ */
