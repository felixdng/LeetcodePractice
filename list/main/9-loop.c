/*
* 给定一个链表，判断链表中是否有环。
* 如果有环则返回链表开始入环的第一个节点，否则返回NULL。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listdemo.h"


/* iteration */
slist_t *has_loop(slist_t *node)
{
	slist_t *fast = node, *slow = node;
	slist_t *ret = NULL;

	while (1) {
		if (NULL == ret) {
			if (NULL == fast || NULL == fast->next)
				return NULL;
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow)
				ret = node;
		} else if (ret == slow) {
			return ret;
		} else {
			ret = ret->next;
			slow = slow->next;
		}
	}
}

/* recursion */
slist_t *has_loop_recu(slist_t *node)
{
	return NULL;
}

void show_usage(int argc, char *argv[])
{
	printf("Usage: %s <algo> <list> <N>\n", argv[0]);
	printf("algo :\n");
	printf("  -i        Iteration algorithm.\n");
	printf("  -r        Recursion algorithm.\n");
	printf("list:       Link list.\n");
	printf("N:          Position of loop.");
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

	slist_t *pos = NULL, *tail = NULL;
	slist_t *ret = NULL, *p = head.next;

	while (NULL != p) {
		if (NULL == p->next)
			tail = p;
		if (1 == n)
			pos = p;

		n--;
		p = p->next;
	}
	if (NULL != tail)
		tail->next = pos;
	
	if (0 == algo)
		ret = has_loop(head.next);
	else if (1 == algo)
		ret = has_loop_recu(head.next);

	if (NULL == ret)
		printf("loop not exist.\n");
	else {
		printf("loop exist, %lld\n", TO_LISTNODE_VAL(ret));
	}

	if (NULL != tail)
		tail->next = NULL;
	demo_list_destroy(&head);
	return 0;
}
