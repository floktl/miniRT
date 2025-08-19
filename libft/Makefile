# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Florian Keitel <fl.keitelgmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 09:46:50 by fkeitel           #+#    #+#              #
#    Updated: 2025/08/18 20:41:50 by Florian Kei      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FT_PRINTFDIR = print_functions/ft_printf
GET_NEXT_LINEDIR = print_functions/get_next_line

FUNCTIONS = conversion/ft_atoi.c conversion/ft_atof.c conversion/ft_itoa.c conversion/ft_tolower.c conversion/ft_toupper.c \
	list_functions/ft_lstadd_back.c list_functions/ft_lstadd_front.c list_functions/ft_lstclear.c list_functions/ft_lstdelone.c list_functions/ft_lstiter.c list_functions/ft_lstlast.c list_functions/ft_lstmap.c list_functions/ft_lstnew.c list_functions/ft_lstsize.c \
	memory_manipulation/ft_bzero.c memory_manipulation/ft_calloc.c memory_manipulation/ft_memchr.c memory_manipulation/ft_memcmp.c memory_manipulation/ft_memcpy.c memory_manipulation/ft_memmove.c memory_manipulation/ft_memset.c memory_manipulation/ft_realloc.c \
	string_checks/ft_isalnum.c string_checks/ft_isalpha.c string_checks/ft_isascii.c string_checks/ft_isdigit.c string_checks/ft_isprint.c string_checks/ft_strlen.c \
	string_manipulation/ft_split.c string_manipulation/ft_strdup.c string_manipulation/ft_striteri.c string_manipulation/ft_strjoin.c string_manipulation/ft_strlcat.c string_manipulation/ft_strlcpy.c string_manipulation/ft_strmapi.c string_manipulation/ft_strncmp.c string_manipulation/ft_strnstr.c string_manipulation/ft_strrchr.c string_manipulation/ft_strtrim.c string_manipulation/ft_substr.c string_manipulation/free_two_dimensional_array.c string_manipulation/ft_strchr.c \
	print_functions/ft_putchar_fd.c print_functions/ft_putendl_fd.c print_functions/ft_putnbr_fd.c print_functions/ft_putstr_fd.c

FT_PRINTF = $(FT_PRINTFDIR)/ft_printf.c $(FT_PRINTFDIR)/check_datatypes.c $(FT_PRINTFDIR)/printing_functions.c $(FT_PRINTFDIR)/handle_datatypes.c

GET_NEXT_LINE = $(GET_NEXT_LINEDIR)/get_next_line_utils.c $(GET_NEXT_LINEDIR)/get_next_line.c

OBJ_DIR = obj

OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(FUNCTIONS)) $(patsubst %.c,$(OBJ_DIR)/%.o,$(FT_PRINTF)) $(patsubst %.c,$(OBJ_DIR)/%.o,$(GET_NEXT_LINE))

CC = cc -g
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/conversion $(OBJ_DIR)/list_functions $(OBJ_DIR)/memory_manipulation $(OBJ_DIR)/print_functions/ft_printf $(OBJ_DIR)/print_functions/get_next_line $(OBJ_DIR)/string_checks $(OBJ_DIR)/string_manipulation

clean:
	$(RM) $(OBJECTS) all
	rm -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	rm -f libft

re: fclean all

.PHONY: all clean fclean
