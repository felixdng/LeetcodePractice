/*
* [合并两个有序链表]
* 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
* 示例：
* 输入：1->2->4, 1->3->4
* 输出：1->1->2->3->4->4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listdemo.h"

/* iteration */
slist_t *merge_two(slist_t *l1, slist_t *l2)
{
	SLIST_HEAD(dummy);
	slist_t *prev = &dummy;
	while (1) {
		if (NULL == l1 || NULL == l2) {
			prev->next = NULL != l1 ? l1 : l2;
			break;
		}
		if (TO_LISTNODE_VAL(l1) < TO_LISTNODE_VAL(l2)) {
			prev->next = l1;
			prev = l1;
			l1 = l1->next;
		} else {
			prev->next = l2;
			prev = l2;
			slist_t *tmp = l2->next;
			l2->next = l1;
			l2 = tmp;
		}
	}
	return dummy.next;
}

/* recursion */
slist_t *merge_two_recu(slist_t *l1, slist_t *l2)
{
	if (NULL == l1 || NULL == l2)
		return NULL != l1 ? l1 : l2;

	if (TO_LISTNODE_VAL(l1) < TO_LISTNODE_VAL(l2)) {
		l1->next = merge_two_recu(l1->next, l2);
		return l1;
	} else {
		l2->next = merge_two_recu(l1, l2->next);
		return l2;
	}
}

void show_usage(int argc, char *argv[])
{
	printf("Usage: %s <algo> <list1> <list2>\n", argv[0]);
	printf("algo :\n");
	printf("  -i        Iteration algorithm.\n");
	printf("  -r        Recursion algorithm.\n");
	printf("list1:      Ascending linked list.\n");
	printf("list2:      Ascending linked list.\n");
	printf("eg: %s -i \"1 2 3 4\" \"5 6 7\"\n", argv[0]);
}

int main(int argc, char *argv[])
{
	if (argc != 4) {
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

	SLIST_HEAD(l1);
	SLIST_HEAD(l2);
	SLIST_HEAD(rt);

	demo_list_create(argv[2], &l1);
	printf("input list 1 : ");
	demo_list_print(&l1);

	demo_list_create(argv[3], &l2);
	printf("input list 2 : ");
	demo_list_print(&l2);

	if (0 == algo)
		rt.next = merge_two(l1.next, l2.next);
	else if (1 == algo)
		rt.next = merge_two_recu(l1.next, l2.next);

	printf("output list  : ");
	demo_list_print(&rt);

	demo_list_destroy(&rt);
	return 0;
}
