#include "yp_header.h"

#ifndef YP_FUNC_H
#define YP_FUNC_H

int fp_close_all(FILE **fp, int prog);
char **fp_exist_progs(FILE *fp);

int yp_parent_ps();
int yp_child_ps();
void yp_pid_checker(pid_t pid);
int yp_pid();

#endif

