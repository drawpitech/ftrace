/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** stack
*/

#pragma once

#include "array.h"

typedef struct {
    array_t *stack;
} item_stack_t;

item_stack_t *stack_init(item_stack_t *stack);
void stack_push(item_stack_t *stack, void *item);
void *stack_pop(item_stack_t *stack);
bool stack_is_empty(item_stack_t *stack);
