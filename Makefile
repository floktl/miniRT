# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 14:26:27 by fkeitel           #+#    #+#              #
#    Updated: 2025/08/18 20:36:01 by Florian Kei      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT
CC := /usr/bin/clang
CXX := /usr/bin/clang++
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -O3 -ffast-math -g -Wno-unused-parameter -Wno-unused-function

ifneq ($(TEST), )
CFLAGS += -Wno-unused-parameter -Wno-unused-function
endif

LIBMLX := ./MLX42
LIBMLX_URL := https://github.com/codam-coding-college/MLX42.git
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
HEADERS := -I ./include -I $(LIBMLX)/include

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
	@cmake -S $(LIBMLX) -B $(LIBMLX)/build
	@cmake --build $(LIBMLX)/build --parallel 4

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

test:
	$(MAKE) TEST=1

leaks:
	$(MAKE) LEAKS=1

start: leaks
	./$(NAME) sample.rt

mlxfclean: fclean
	@rm -rf $(LIBMLX)
	@rm -rf MLX42

.PHONY: all clean fclean re libmlx test leaks start
