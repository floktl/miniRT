# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 14:26:27 by fkeitel           #+#    #+#              #
#    Updated: 2025/10/06 18:35:52 by mezhang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT
CC := gcc
CXX := g++
CFLAGS := -Wall -Wextra -Wno-error -Wunreachable-code -O0 -ffast-math -g \
			-Wno-unused-parameter -Wno-unused-function -Wno-unused-variable

ifneq ($(TEST), )
CFLAGS += -Wno-unused-parameter -Wno-unused-function
endif

LIBMLX := ./MLX42
LIBMLX_URL := https://github.com/codam-coding-college/MLX42.git
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
HEADERS := -I ./include -I $(LIBMLX)/include -I $(LIBFT_DIR)

# Directories
SRC_DIR := srcs
OBJ_DIR := obj

LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L$(LIBFT_DIR) -lft

ifneq ($(LEAKS), )
LEAKFLAGS := -L/Users/flo/LeakSanitizer -llsan
endif

SRCS := $(shell find $(SRC_DIR) -name '*.c')

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(LIBFT) libmlx $(NAME)
	@echo "$(NAME) successfully built!"

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
			git clone $(LIBMLX_URL) $(LIBMLX); \
	fi
	@if [ ! -f "$(LIBMLX)/build/libmlx42.a" ]; then \
		cmake -S $(LIBMLX) -B $(LIBMLX)/build; \
		cmake --build $(LIBMLX)/build --parallel 4; \
	else \
		echo "MLX42 already compiled, skipping..."; \
	fi

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Ensure the obj directory and necessary subdirectories are created
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(LEAKFLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

mlxfclean: fclean
	@rm -rf $(LIBMLX)
	@rm -rf MLX42

.PHONY: all clean fclean re libmlx

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT sample.rt
