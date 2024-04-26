/*
** EPITECH PROJECT, 2024
** server
** File description:
** array
*/

#include "array.h"
#include <stdlib.h>

int add_elt_to_array(array_t *array, void *element)
{
    if (array->nb_elements + 1 == DEFAULT_SIZE) {
        array->element = realloc(array->element, array->size * 2);
        if (NULL == array->element)
            return FAILURE;
        array->size *= 2;
    }
    array->element[array->nb_elements] = element;
    array->nb_elements++;
    return 0;
}

int remove_elt_to_array(array_t *array, size_t i)
{
    void *tmp = array->element[i];

    array->element[i] = array->element[array->nb_elements - 1];
    array->element[array->nb_elements - 1] = tmp;
    array->nb_elements--;
    return SUCCESS;
}

array_t *array_constructor(void)
{
    array_t *array = malloc(sizeof(array_t));

    if (!array)
        return NULL;
    array->nb_elements = 0;
    array->size = DEFAULT_SIZE;
    array->element = calloc(DEFAULT_SIZE, sizeof(void *));
    if (!array->element)
        return NULL;
    return array;
}
