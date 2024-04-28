/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** get_elf_symbols
*/

#pragma once

#include <gelf.h>
#include <libelf.h>

#include "array.h"

typedef struct {
    const char *path;
    int fd;
    Elf *elf;
    GElf_Shdr shdr;
    size_t shstrndx;
    array_t *symbols;
} elf_file_t;

typedef struct {
    uintmax_t addr;
    char *name;
} symbol_t;

bool elf_file_get_symbols(elf_file_t *file, const char *filename);
void elf_file_unload_symbols(elf_file_t *file);
