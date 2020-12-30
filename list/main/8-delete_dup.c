/*
* [删除排序链表中的重复元素]
* 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。
* 示例 1:
* 输入: 1->1->2
* 输出: 1->2
* 示例 2:
* 输入: 1->1->2->3->3
* 输出: 1->2->3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listdemo.h"

/* iteration */
slist_t *delete_dup(slist_t *node)
{
	slist_t *cur = node, *next = node;
	while (NULL != next) {
		if (TO_LISTNODE_VAL(cur) != TO_LISTNODE_VAL(next)) {
			cur->next = next;
			cur = next;
			next = cur->next;
		} else if (NULL == next->next) {
			cur->next = NULL;
			break;
		} else {
			//free next
			next = next->next;
		}
	}

	return node;
}

/* recursion */
slist_t *delete_dup_recu(slist_t *node)
{
	return node;
}

void show_usage(int argc, char *argv[])
{
	printf("Usage: %s <algo> <list>\n", argv[0]);
	printf("algo :\n");
	printf("  -i        Iteration algorithm.\n");
	printf("  -r        Recursion algorithm.\n");
	printf("list:       Link list.\n");
	printf("eg: %s -i \"1 2 2 3 3 4\"\n", argv[0]);
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
		head.next = delete_dup(head.next);
	else if (1 == algo)
		head.next = delete_dup_recu(head.next);

	printf("output list : ");
	demo_list_print(&head);

	demo_list_destroy(&head);
	return 0;
}
