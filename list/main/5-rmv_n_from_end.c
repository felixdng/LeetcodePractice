/*
* 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
* 示例：
* 给定一个链表: 1->2->3->4->5, 和 n = 2.
* 当删除了倒数第二个节点后，链表变为 1->2->3->5.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listdemo.h"

/* iteration */
slist_t *rmv_n_from_end(slist_t *node, int n)
{
	SLIST_HEAD(dummy);
	dummy.next = node;
	slist_t *fast = &dummy, *slow = &dummy;
	int i = 0;
	for (i = 0; i < n; i++) {
		if (NULL == fast->next)
			break;
		fast = fast->next;
	}
	if (fast == slow || i < n)
		return dummy.next;
	while (NULL != fast->next) {
		fast = fast->next;
		slow = slow->next;
	}
	//free slow->next
	slow->next = slow->next->next;
	return dummy.next;
}

/* recursion */
slist_t *rmv_n_from_end_recu(slist_t *node, int n)
{
	return node;
}

void show_usage(int argc, char *argv[])
{
	printf("Usage: %s <algo> <list> <N>\n", argv[0]);
	printf("algo :\n");
	printf("  -i        Iteration algorithm.\n");
	printf("  -r        Recursion algorithm.\n");
	printf("list:       Link list.\n");
	printf("N:          N from end.\n");
	printf("eg: %s -i \"1 2 3 4\" 2\n", argv[0]);
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

	size_t liststr_len = strlen(argv[2]);
	char liststr[liststr_len + 1];
	memset(liststr, 0, liststr_len + 1);
	strncpy(liststr, argv[2], liststr_len);

	int n = strtoul(argv[3], NULL, 0);

	slist_t head;
	INIT_SLIST_HEAD(&head);

	demo_list_create(liststr, &head);
	printf("input list  : ");
	demo_list_print(&head);

	if (0 == algo)
		head.next = rmv_n_from_end(head.next, n);
	else if (1 == algo)
		head.next = rmv_n_from_end_recu(head.next, n);

	printf("output list : ");
	demo_list_print(&head);

	demo_list_destroy(&head);
	return 0;
}
