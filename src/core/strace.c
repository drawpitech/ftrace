/*
** EPITECH PROJECT, 2024
** y2
** File description:
** strace
*/

#include "strace.h"
#include "context.h"
#include "errors.h"
#include "map_mem.h"
#include "syscall.h"

#include <bits/types/siginfo_t.h>
#include <signal.h>
#include <stdlib.h>
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

static void display_signal(siginfo_t signal)
{
    for (size_t i = 0; i < 30; ++i) {
        if (signals[i].code == signal.si_signo) {
            printf("Received signal %s\n", signals[i].signal);
            return;
        }
    }
}


long handle_end_of_prog(context_t *ctx, int status)
{
    long exit_status = 0;

    if (ptrace(PTRACE_GETEVENTMSG, ctx->m_pid, 0, &status) == -1)
        return 84;
    exit_status = WEXITSTATUS(status);
    fprintf(stderr, "+++ exited with %ld +++\n", exit_status);
    return exit_status;
}

static void handle_signal(context_t *ctx, int status)
{
    siginfo_t signal;

    if (status >> 8 == (SIGTRAP | (PTRACE_EVENT_EXIT << 8)))
        handle_end_of_prog(ctx, status);
    else if (ptrace(PTRACE_GETSIGINFO, ctx->m_pid, 0, &signal) >= 0 &&
        signal.si_signo != SIGTRAP && signal.si_signo != SIGSTOP)
        display_signal(signal);
    return;
}

int trace(context_t *ctx)
{
    int status = 0;

    waitpid(ctx->m_pid, &status, 0);
    if (WIFEXITED(status))
        return 0;
    if (ptrace(PTRACE_SETOPTIONS, ctx->m_pid, 0, PTRACE_O_TRACEEXIT) == -1)
        return print_error(PTRACE_FAILED);
    stack_init(&ctx->call_stack);
    for (;;) {
        handle_signal(ctx, status);
        if (WIFEXITED(status))
            break;
        if (ptrace(PTRACE_GETREGS, ctx->m_pid, 0, &ctx->m_regs) == -1)
            return print_error(PTRACE_FAILED);
        display_syscall(ctx);
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
