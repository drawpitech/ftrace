/*
** EPITECH PROJECT, 2024
** core
** File description:
** get_function_name */

#include "array.h"
#include "context.h"
#include "map_mem.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>


static map_item_t *get_data(map_item_t *lib, char *line)
{
    char *lib_path = NULL;
    char *start_ptr = NULL;
    char *end_ptr = NULL;

    start_ptr = strsep(&line, "-");
    end_ptr = strsep(&line, "-");
    if (strstr(line, "/") == NULL)
        return NULL;
    lib_path = strstr(line, "/");
    lib_path[strlen(lib_path) - 1] = '\0';
    strcpy(lib->m_path, lib_path);
    lib->m_start_addr = strtol(start_ptr, NULL, 16);
    lib->m_end_addr = strtol(end_ptr, NULL, 16);
    return lib;
}

static void parse_lib(context_t *ctx)
{
    FILE *f;
    char *line = NULL;
    size_t len = 0;
    char buffer[DEFAULT_SIZE];
    map_item_t *lib = malloc(sizeof(map_item_t));

    sprintf(buffer, "/proc/%d/maps", ctx->m_pid);
    f = fopen(buffer, "r");
    while (getline(&line, &len, f))
        if (NULL != line)
            add_elt_to_array(ctx->process, get_data(lib, line));
    fclose(f);
}

static char *format_name(char *name, unsigned long addr)
{
    char buffer[DEFAULT_SIZE] = {0};

    sprintf(buffer, "func_%#lx@%s", addr, name);
    return strdup(buffer);
}

char *get_function_name(context_t *ctx, long addr)
{
    map_item_t *read = NULL;

    if (0 == ctx->process->nb_elements)
        parse_lib(ctx);
    if (0 == ctx->process->nb_elements)
        return format_name(ctx->m_argv[1], addr);
    for (size_t i = 0; i < ctx->process->nb_elements; ++i) {
        read = ctx->process->element[i];
        if (addr >= read->m_start_addr && addr <= read->m_end_addr)
            return read->m_path;
    }
    return NULL;
}
