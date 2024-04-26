/*
** EPITECH PROJECT, 2024
** y2
** File description:
** strace_display
*/

#include "map_mem.h"
#include "context.h"
#include <sys/ptrace.h>
#include "syscall.h"
#include <stdio.h>
#include <stdint.h>

static void classic_display(context_t *ctx)
{
    unsigned long long registers[] = {ctx->m_regs.rdi, ctx->m_regs.rsi,
    ctx->m_regs.rdx, ctx->m_regs.r9, ctx->m_regs.r8, ctx->m_regs.rcx};
    unsigned long long orig_rax = ctx->m_regs.orig_rax;
    syscall_t val = get_syscall_by_id(orig_rax);

    printf("%s(", val.m_name);
    if (val.m_nb_args == 0) {
        printf(") = ");
        return;
    }
    for (int i = 0; i < val.m_nb_args; i++) {
        printf("0x%llx", registers[i]);
        if (i < val.m_nb_args - 1)
            printf(", ");
    }
    printf(") = ");
}

static void display_ret(context_t *ctx)
{
    unsigned long long orig_rax = ctx->m_regs.orig_rax;
    syscall_t val = get_syscall_by_id(orig_rax);

    if (orig_rax == 60 || orig_rax == 231) {
        printf("?\n");
        printf("+++ exited with %lld +++\n", ctx->m_regs.rdi);
        return;
    }
    if (val.m_retn_type == VOID)
        printf("?\n");
    else
        printf("0x%llx\n", ctx->m_regs.rax);
}

static void display(context_t *ctx)
{
    printf("%s(", get_syscall_by_id(ctx->m_regs.orig_rax).m_name);
    if (ctx->m_regs.orig_rax == 59) {
        printf("\"%s\", [\"%s\"], ", ctx->m_argv[0], ctx->m_argv[0]);
        printf("0x%llx /* %d vars */)\n", ctx->m_regs.rdx, 0);
        return;
    }
    classic_display(ctx);
    display_ret(ctx);
}

static void display_func_call(context_t *ctx)
{
    printf(
        "\033[1;5;91m[here]\033[m "
        "Entering function at 0x%lld\n",
        ctx->m_regs.rip);
}

void display_syscall(context_t *ctx)
{
    uint64_t orig_rax = ctx->m_regs.orig_rax;

    if ((int)orig_rax == -1) {
        //display_func_call(ctx);
        return;
    }
    if (orig_rax > SYSCALLS_AMOUNT)
        return;
    display(ctx);
}
