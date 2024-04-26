##
## EPITECH PROJECT, 2024
## rush2
## File description:
## Makefile
##

SRC 		:= 	$(shell find src/ -name '*.c')

BUILD_DIR 	:= 	build

NAME		:= ftrace

CC 			:= 	gcc
CFLAGS 		:= 	-std=gnu17 -Wall -Wextra -MMD -MP
OBJ 		:= 	$(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))

all: $(NAME)

-include $(OBJ:.o=.d)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

.NOTPARALLEL: re
re: fclean all

.PHONY: all clean fclean re
