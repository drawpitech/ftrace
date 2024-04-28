/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** get_elf_symbols
*/

#include "get_elf_symbols.h"

#include <fcntl.h>
#include <gelf.h>
#include <libelf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "array.h"

static bool elf_file_load_symbols(elf_file_t *file)
{
    if (elf_version(EV_CURRENT) == EV_NONE)
        return false;
    file->fd = open(file->path, O_RDONLY, 0);
    if (file->fd < 0)
        return false;
    file->elf = elf_begin(file->fd, ELF_C_READ, NULL);
    if (file->elf == NULL)
        return close(file->fd), false;
    if (elf_getshdrstrndx(file->elf, &file->shstrndx) != 0)
        return elf_file_unload_symbols(file), false;
    return true;
}

static void elf_file_get_symbol(GElf_Sym sym, elf_file_t *file)
{
    const char *name = elf_strptr(file->elf, file->shdr.sh_link, sym.st_name);
    symbol_t *symbol = malloc(sizeof *symbol);

    if (name == NULL)
        return;
    symbol->addr = sym.st_value;
    symbol->name = name;
    add_elt_to_array(file->symbols, symbol);
}

static void elf_file_get_symtab(elf_file_t *file, Elf_Scn *scn)
{
    GElf_Sym sym;
    int n_symbols = 0;
    Elf_Data *data = elf_getdata(scn, NULL);

    if (data == NULL)
        return;
    n_symbols = (int)(file->shdr.sh_size / file->shdr.sh_entsize);
    for (int i = 0; i < n_symbols; ++i) {
        if (gelf_getsym(data, i, &sym) != &sym)
            return;
        elf_file_get_symbol(sym, file);
    }
}

bool elf_file_get_symbols(elf_file_t *file, const char *filename)
{
    Elf_Scn *scn = NULL;

    file->path = filename;
    if (!elf_file_load_symbols(file))
        return false;
    file->symbols = array_constructor();
    for (;;) {
        scn = elf_nextscn(file->elf, scn);
        if (scn == NULL)
            break;
        if (gelf_getshdr(scn, &file->shdr) != &file->shdr)
            return false;
        if (file->shdr.sh_type == SHT_SYMTAB ||
            file->shdr.sh_type == SHT_DYNSYM)
            elf_file_get_symtab(file, scn);
    }
    return true;
}

void elf_file_unload_symbols(elf_file_t *file)
{
    elf_end(file->elf);
    close(file->fd);
    for (size_t i = 0; i < file->symbols->nb_elements; ++i)
        free(file->symbols->element[i]);
    free(file->symbols->element);
}
