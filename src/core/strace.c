/*
** EPITECH PROJECT, 2024
** y2
** File description:
** strace
*/

#include "strace.h"
#include "errors.h"
#include "strace_display.h"

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int exec_trace(context_t *ctx)
{
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1)
        return print_error(PTRACE_FAILED);
    execvp(ctx->m_argv[0], ctx->m_argv);
    return 0;
}

int trace(context_t *ctx)
{
    int status = 0;

    wait(&status);
    if (WIFEXITED(status))
        return 0;
    if (ptrace(PTRACE_SETOPTIONS, ctx->m_pid, 0, PTRACE_O_TRACEEXIT) == -1)
        return print_error(PTRACE_FAILED);
    while (1) {
        if (WIFEXITED(status))
            break;
        if (ptrace(PTRACE_GETREGS, ctx->m_pid, 0, &ctx->m_regs) == -1)
            return print_error(PTRACE_FAILED);
        display_syscall(ctx);
        //printf("Entering function at %lld\n", ctx->m_regs.rip);
        if (ptrace(PTRACE_SINGLESTEP, ctx->m_pid, 0, 0) == -1)
            return print_error(PTRACE_FAILED);
        wait(&status);
    }
    return 0;
}

int strace(context_t *ctx)
{
    ctx->m_pid = fork();
    if (ctx->m_pid == -1)
        return print_error(FORK_FAILED);
    if (ctx->m_pid == 0)
        return exec_trace(ctx);
    return trace(ctx);
}
