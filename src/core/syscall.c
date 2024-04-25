/*
** EPITECH PROJECT, 2024
** y2
** File description:
** syscall
*/

#include "syscall.h"
#include "context.h"

syscall_t get_syscall_by_id(int id)
{
    if (id < 0 || id > SYSCALLS_AMOUNT)
        return (syscall_t){
            -1,
            "unknown syscall",
            0, 0, 0, 0, 0, 0, 0, 0
        };
    return g_syscalls[id];
}

int get_arg_type_by_id(syscall_t *syscall, int arg)
{
    if (arg < 0 || arg > syscall->m_nb_args)
        return 0;
    switch (arg) {
    case 0:
        return syscall->m_arg1;
    case 1:
        return syscall->m_arg2;
    case 2:
        return syscall->m_arg3;
    case 3:
        return syscall->m_arg4;
    case 4:
        return syscall->m_arg5;
    case 5:
        return syscall->m_arg6;
    }
    return 0;
}
