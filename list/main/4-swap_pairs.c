/*
* 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
* 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listdemo.h"

/* iteration */
slist_t *swap_pairs(slist_t *node)
{
	slist_t dummy;
	INIT_SLIST_HEAD(&dummy);
	dummy.next = node;
	slist_t *tail = &dummy;
	slist_t *p = node;

	while (NULL != p && NULL != p->next) {
		slist_t *tmp = p->next->next;
		tail->next = p->next;
		p->next->next = p;
		p->next = tmp;
		tail = p;
		p = tmp;
	}
	return dummy.next;
}

/* recursion */
slist_t *swap_pairs_recu(slist_t *node)
{
	if (NULL == node || NULL == node->next)
		return node;
	slist_t *ret = node->next;
	slist_t *tmp = swap_pairs_recu(node->next->next);
	node->next->next = node;
	node->next = tmp;
	return ret;
}

void show_usage(int argc, char *argv[])
{
	printf("Usage: %s <algo> <list>\n", argv[0]);
	printf("algo :\n");
	printf("  -i        Iteration algorithm.\n");
	printf("  -r        Recursion algorithm.\n");
	printf("list:       Link list.\n");
	printf("eg: %s -i \"1 2 3 4\"\n", argv[0]);
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		show_usage(argc, argv);
		return 1;
	}

	int algo = 0;
	if (0 == strcmp(argv[1], "-i"))
		algo = 0;
	else if (0 == strcmp(argv[1], "-r"))
		algo = 1;
	else {
		show_usage(argc, argv);
		return 1;
	}

	size_t liststr_len = strlen(argv[2]);
	char liststr[liststr_len + 1];
	memset(liststr, 0, liststr_len + 1);
	strncpy(liststr, argv[2], liststr_len);

	slist_t head;
	INIT_SLIST_HEAD(&head);

	demo_list_create(liststr, &head);
	printf("input list  : ");
	demo_list_print(&head);

	if (0 == algo)
		head.next = swap_pairs(head.next);
	else if (1 == algo)
		head.next = swap_pairs_recu(head.next);

	printf("output list : ");
	demo_list_print(&head);

	return 0;
}
