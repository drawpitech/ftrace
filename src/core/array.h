/*
** EPITECH PROJECT, 2024
** include
** File description:
** server
*/

#pragma once

#include <unistd.h>
#include <stdbool.h>
#include <uuid/uuid.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DEFAULT_SIZE 1024
#define MAX_PATH 4096
#define SUCCESS 0
#define FAILURE 84
#define LEN(a) (sizeof(a) / sizeof(*a))

typedef struct array_s {
    size_t size;
    size_t nb_elements;
    void **element;
} array_t;

array_t *array_constructor(void);
int add_elt_to_array(array_t *array, void *element);
int remove_elt_to_array(array_t *array, size_t i);
char **my_str_to_word_array(char const *str, char const *separator);
