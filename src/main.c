/*
** EPITECH PROJECT, 2024
** y2
** File description:
** main
*/

#include "core/errors.h"
#include "core/context.h"
#include "core/strace.h"
#include <string.h>

static char **get_args(char **argv)
{
    return &argv[1];
}

static int initialize(int argc, char **argv)
{
    context_t ctx;

    (void)argc;
    ctx.m_argv = get_args(argv);
    return strace(&ctx);
}

int main(int argc, char *argv[])
{
    if (2 != argc)
        return print_error(MISSING_ARG);
    if (initialize(argc, argv) != 0)
        return 84;
    return 0;
}
