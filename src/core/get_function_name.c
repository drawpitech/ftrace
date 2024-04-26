/*
** EPITECH PROJECT, 2024
** core
** File description:
** get_function_name
*/

#include "array.h"
#include "context.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static void parse_lib(context_t *ctx)
{
    FILE *f;
    char *line = NULL;
    size_t len = 0;
    char buffer[DEFAULT_SIZE];

    sprintf(buffer, "/proc/%d/maps", ctx->m_pid);
    f = fopen(buffer, "r");
    while (getline(&line, &len, f))
        if (NULL != line)
            add_elt_to_array(ctx->process, line);
    fclose(f);
}

char *get_function_name(context_t *ctx, long addr)
{
    if (0 == ctx->process->nb_elements)
        parse_lib(ctx);
    return NULL;
}
