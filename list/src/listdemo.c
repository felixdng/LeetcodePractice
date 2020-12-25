#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listdemo.h"
#include "log.h"

#define ERR(fmt, ...) \
pr_err("[%s:L%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)


slist_t * demo_list_create(const char *str, slist_t *lh)
{
	if (NULL == lh) {
		ERR("lh is null!");
		return NULL;
	} else if (NULL != lh->next) {
		ERR("lh is not empty!");
		return NULL;
	}

	if (NULL == str) {
		ERR("str is null!");
		return NULL;
	}

	const char *pos = str;
	while (NULL != pos && '\0' != *pos) {
		if ((*pos >= '0' && *pos <= '9') || *pos == '-' || *pos == '+') {
			char *tmp = NULL;
			long long int val = strtoul(pos, &tmp, 0);
			pos = tmp;

			listnode_t *node = (listnode_t *)calloc(1, sizeof(listnode_t));
			if (NULL == node) {
				ERR("calloc failed!");
				demo_list_destroy(lh);
				return NULL;
			}
			node->val = val;
			slist_add_tail(TO_SLIST(node), lh);
		} else {
			pos++;
		}
	}

	return lh;
}

void demo_list_destroy(slist_t *lh)
{
	slist_t *pos, *next;
	slist_for_each_safe(pos, next, lh) {
		slist_del(pos, lh);
		free(pos);
	}
}

void demo_list_print(slist_t *lh)
{
	printf("[ ");
	slist_t *pos, *next;
	slist_for_each_safe(pos, next, lh) {
		printf("%lld ", TO_LISTNODE_VAL(pos));
	}
	printf("]\n");
}

