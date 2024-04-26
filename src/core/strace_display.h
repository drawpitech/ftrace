/*
** EPITECH PROJECT, 2024
** y2
** File description:
** strace_display
*/

#pragma once

#include <stddef.h>
#include <linux/limits.h>
#include "context.h"

typedef struct {
    char m_path[PATH_MAX];
    ptrdiff_t m_start_addr;
    ptrdiff_t m_end_addr;
} map_item_t;

typedef struct {
    map_item_t *m_items;
    size_t m_len;
    size_t m_capacity;
} maps_t;

void display_syscall(context_t *ctx);
