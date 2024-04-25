/*
** EPITECH PROJECT, 2024
** y2
** File description:
** utils
*/

#include "utils.h"
#include <stdlib.h>
#include <sys/ptrace.h>
#include <string.h>

// TODO: manage in case register string is bigger than the malloc'd size
char *get_reg_string(context_t *ctx, unsigned long long reg)
{
    char *str = malloc(1024);
    unsigned long long tmp_trace = 0;

    for (unsigned long i = 0;; i += sizeof(unsigned long)) {
        tmp_trace = ptrace(PTRACE_PEEKDATA, ctx->m_pid, reg + i, 0);
        if ((int)tmp_trace < 0)
            break;
        memcpy(str + i, &tmp_trace, sizeof(tmp_trace));
        if (memchr(&tmp_trace, 0, sizeof(tmp_trace)))
            break;
    }
    return str;
}
