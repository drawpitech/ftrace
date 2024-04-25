/*
** EPITECH PROJECT, 2024
** y2
** File description:
** errors
*/

#pragma once

typedef enum error_e {
    REQUIRE_ARG = 1,
    MISSING_ARG = 2,
    FORK_FAILED = 3,
    PTRACE_FAILED = 4,
    WAIT_FAILED = 5,
} error_t;

typedef struct error_msg_s {
    error_t error;
    char *msg;
} error_msg_t;

static const error_msg_t g_errors[] = {
    {REQUIRE_ARG, "./strace: flag require an argument."},
    {MISSING_ARG, "./strace: must have PROG [ARGS] or -p PID.\n"},
    {FORK_FAILED, "./strace: fork failed.\n"},
    {PTRACE_FAILED, "./strace: ptrace failed.\n"},
    {WAIT_FAILED, "./strace: wait failed.\n"},
    {0, 0},
};

int print_error(error_t error);
