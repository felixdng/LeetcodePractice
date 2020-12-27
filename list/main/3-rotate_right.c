/*
* 给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
* 示例 1:
* 输入: 1->2->3->4->5->NULL, k = 2
* 输出: 4->5->1->2->3->NULL
* 解释:
* 向右旋转 1 步: 5->1->2->3->4->NULL
* 向右旋转 2 步: 4->5->1->2->3->NULL
* 示例 2:
* 输入: 0->1->2->NULL, k = 4
* 输出: 2->0->1->NULL
* 解释:
* 向右旋转 1 步: 2->0->1->NULL
* 向右旋转 2 步: 1->2->0->NULL
* 向右旋转 3 步: 0->1->2->NULL
* 向右旋转 4 步: 2->0->1->NULL
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listdemo.h"

/* iteration */
slist_t *rotate_right(slist_t *node, int k)
{
	int len = 0, _k = k;
	slist_t *fast = node, *slow = node;
	while (NULL != fast) {
		if (0 >= _k) break;
		if (NULL == fast->next && len < _k) {
			_k = _k % (len + 1);
			fast = node;
			slow = node;
			len = 0;
			continue;
		} else if (NULL == fast->next)
			break;

		if (len >= _k)
			slow = slow->next;
		fast = fast->next;
		len++;
	}
	if (fast != slow) {
		slist_t *tmp = slow->next;
		slow->next = NULL;
		fast->next = node;
		return tmp;
	} else
		return node;
}

/* recursion */
slist_t *rotate_right_recu(slist_t *node, int k)
{
	return node;
}

void show_usage(int argc, char *argv[])
{
	printf("Usage: %s <algo> <list> <k>\n", argv[0]);
	printf("algo :\n");
	printf("  -i        Iteration algorithm.\n");
	printf("  -r        Recursion algorithm.\n");
	printf("list:       Link list.\n");
	printf("m:          The counter of rotate right.");
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

	int k = strtoul(argv[3], NULL, 0);

	slist_t head;
	INIT_SLIST_HEAD(&head);

	demo_list_create(liststr, &head);
	printf("input list  : ");
	demo_list_print(&head);

	if (0 == algo)
		head.next = rotate_right(head.next, k);
	else if (1 == algo)
		head.next = rotate_right_recu(head.next, k);

	printf("output list : ");
	demo_list_print(&head);

	return 0;
}
