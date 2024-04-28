/*
** EPITECH PROJECT, 2024
** ftrace
** File description:
** stack
*/

#include "stack.h"

#include <stdbool.h>
#include <stdlib.h>

#include "array.h"

item_stack_t *stack_init(item_stack_t *stack)
{
    if (stack == NULL)
        stack = malloc(sizeof *stack);
    stack->stack = array_constructor();
    return stack;
}

void stack_push(item_stack_t *stack, void *item)
{
    if (stack == NULL)
        return;
    add_elt_to_array(stack->stack, item);
}

void *stack_pop(item_stack_t *stack)
{
    if (stack == NULL || stack_is_empty(stack))
        return NULL;
    stack->stack->nb_elements--;
    return stack->stack->element[stack->stack->nb_elements];
}

bool stack_is_empty(item_stack_t *stack)
{
    return stack->stack->nb_elements == 0;
}
