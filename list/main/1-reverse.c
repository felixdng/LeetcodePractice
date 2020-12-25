#include <stdio.h>
#include <string.h>
#include "listdemo.h"

/* iteration */
slist_t *reverse_list(slist_t *node)
{
	if (NULL == node || NULL == node->next)
		return node;
	slist_t *prev = NULL, *cur = node;
	while (NULL != cur) {
		slist_t *tmp = cur->next;
		cur->next = prev;
		prev = cur;
		cur = tmp;
	}
	return prev;
}

/* recursion */
slist_t *reverse_list_recu(slist_t *node)
{
	if (NULL == node || NULL == node->next)
		return node;
	slist_t *ret = reverse_list_recu(node->next);
	node->next->next = node;
	node->next = NULL;
	return ret;
}

void show_usage(int argc, char *argv[])
{
	printf("Usage: %s <algo> <list>\n", argv[0]);
	printf("algo :\n");
	printf("  -i        Iteration algorithm.\n");
	printf("  -r        Recursion algorithm.\n");
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
		head.next = reverse_list(head.next);
	else if (1 == algo)
		head.next = reverse_list_recu(head.next);

	printf("output list : ");
	demo_list_print(&head);

	return 0;
}
