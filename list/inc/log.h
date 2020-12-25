#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <time.h>

#define print_log(pre, fmt, ...) \
do { \
	time_t now = time(NULL); \
	struct tm t = *localtime(&now); \
	fprintf(stdout, pre "[%4d-%02d-%02d %02d:%02d:%02d] " fmt "\n", \
		t.tm_year + 1990, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, \
                ##__VA_ARGS__); \
} while (0)

#define pr_err(fmt, ...) print_log("[Error] ", fmt, ##__VA_ARGS__)
#define pr_info(fmt, ...) print_log("[Info] ", fmt, ##__VA_ARGS__)

#ifdef DEBUG
#define pr_debug(fmt, ...) print_log("[Debug] ", fmt, ##__VA_ARGS__)
#else
#define pr_debug(fmt, ...)
#endif

#endif /* __LOG_H__ */
