/*
* [两数相加]
* 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储一位数字。
* 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
* 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
* 示例：
* 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
* 输出：7 -> 0 -> 8
* 原因：342 + 465 = 807
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listdemo.h"

/* iteration */
slist_t *add_two(slist_t *l1, slist_t *l2)
{
	SLIST_HEAD(ret);
	slist_t *pos = &ret;
	long long int cnt = 0, flag = 0;
	while (NULL != l1 || NULL != l2 || 0 != flag) {
		cnt = flag;
		cnt += NULL != l1 ? TO_LISTNODE_VAL(l1) : 0;
		cnt += NULL != l2 ? TO_LISTNODE_VAL(l2) : 0;
		flag = cnt / 10;
		cnt = cnt % 10;
		pos = demo_list_node_new_tail(cnt, pos);
		l1 = NULL != l1 ? l1->next : l1;
		l2 = NULL != l2 ? l2->next : l2;
	}
	return ret.next;
}

/* recursion */
slist_t *add_two_recu(slist_t *l1, slist_t *l2)
{
	return l1;
}

void show_usage(int argc, char *argv[])
{
	printf("Usage: %s <algo> <list1> <list2>\n", argv[0]);
	printf("algo :\n");
	printf("  -i        Iteration algorithm.\n");
	printf("  -r        Recursion algorithm.\n");
	printf("list1:      Link list.\n");
	printf("list2:      Link list.\n");
	printf("eg: %s -i \"1 2 3 4\" \"5 1 2\"\n", argv[0]);
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
		rt.next = add_two(l1.next, l2.next);

	printf("output list  : ");
	demo_list_print(&rt);

	demo_list_destroy(&l1);
	demo_list_destroy(&l2);
	demo_list_destroy(&rt);
	return 0;
}
