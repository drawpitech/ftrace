/*
** EPITECH PROJECT, 2024
** y2
** File description:
** errors
*/

#include "errors.h"
#include <stdio.h>

int print_error(error_t error)
{
    char *err = NULL;

    for (int i = 0; g_errors[i].error != 0; i++) {
        if (error == g_errors[i].error)
            err = g_errors[i].msg;
    }
    fprintf(stderr, "%s\n", err);
    return 84;
}
