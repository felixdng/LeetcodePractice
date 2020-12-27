/*
* 反转从位置 m 到 n 的链表。请使用一趟扫描完成反转.
* 1 ≤ m ≤ n ≤ 链表长度.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listdemo.h"

/* iteration */
slist_t *reverse_list(slist_t *node, int m, int n)
{
	if (!(m >= 1 && n >= m))
		return node;
	slist_t *pm = NULL, *pm_prev = NULL;
	slist_t *cur = node, *prev = NULL;
	int index = 1;
	while (NULL != cur) {
		if (index == m) {
			pm = cur;
			pm_prev = prev;
		}

		if (index < m) {
			prev = cur;
			cur = cur->next;
		} else if (index >= m && index <= n) {
			slist_t *tmp = cur->next;
			cur->next = prev;
			prev = cur;
			cur = tmp;
		} else {
			break;
		}

		index++;
	}

	if (NULL != pm_prev)
		pm_prev->next = prev;
	if (NULL != pm)
		pm->next = cur;
	return m > 1 ? node : prev;
}

/* recursion */
static slist_t *n_next = NULL;
slist_t *reverse_list_recu(slist_t *node, int m, int n)
{
	slist_t *ret = node;
	if (!(m >= 1 && m <= n) || NULL == node)
		return ret;
	if (1 == n || NULL == node->next) {
		n_next = node->next; //node(n+1)
		return ret;
	}

	if (1 < m) {
		slist_t *next = reverse_list_recu(node->next, m - 1, n - 1);
		//node(m-1)
		if (next != node->next)
			node->next = next;
	} else if (n > 1) {
		ret = reverse_list_recu(node->next, 1, n - 1);
		node->next->next = node;
		node->next = n_next;
	}

	return ret;
}

void show_usage(int argc, char *argv[])
{
	printf("Usage: %s <algo> <list> <m> <n>\n", argv[0]);
	printf("algo :\n");
	printf("  -i        Iteration algorithm.\n");
	printf("  -r        Recursion algorithm.\n");
	printf("list:       Link list.\n");
	printf("m,n:        Between m and n.");
	printf("eg: %s -i \"1 2 3 4\" 2 3\n", argv[0]);
}

int main(int argc, char *argv[])
{
	if (argc != 5) {
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

	int bt_m = strtoul(argv[3], NULL, 0);
	int bt_n = strtoul(argv[4], NULL, 0);

	slist_t head;
	INIT_SLIST_HEAD(&head);

	demo_list_create(liststr, &head);
	printf("input list  : ");
	demo_list_print(&head);

	if (0 == algo)
		head.next = reverse_list(head.next, bt_m, bt_n);
	else if (1 == algo)
		head.next = reverse_list_recu(head.next, bt_m, bt_n);

	printf("output list : ");
	demo_list_print(&head);

	return 0;
}
