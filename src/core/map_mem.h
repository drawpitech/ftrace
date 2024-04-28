/*
** EPITECH PROJECT, 2024
** y2
** File description:
** strace_display
*/

#pragma once

#include <linux/limits.h>
#include <stddef.h>

#include "context.h"
#include "get_elf_symbols.h"

typedef struct {
    char m_path[PATH_MAX];
    ptrdiff_t m_start_addr;
    ptrdiff_t m_end_addr;
    elf_file_t m_elf;
} map_item_t;

void display_syscall(context_t *ctx);
