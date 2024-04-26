/*
** EPITECH PROJECT, 2024
** y2
** File description:
** context
*/

#pragma once
#include <sys/types.h>
#include <sys/user.h>
#include <gelf.h>

#include "array.h"

#define SYSCALLS_AMOUNT 328 // from the syscall.h table

typedef struct elf_content_s {
    Elf *elf;
    GElf_Shdr *shdr;
    Elf_Data *data;
    char *name;
} elf_content_t;

typedef struct context_s {
    pid_t m_pid;
    char **m_argv;
    struct user_regs_struct m_regs;
    array_t *process;
    array_t *symbols;
} context_t;
