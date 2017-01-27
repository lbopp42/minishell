# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbopp <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/27 09:06:43 by lbopp             #+#    #+#              #
#    Updated: 2017/01/27 16:06:07 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra -g
LIBFT = libft/
CC = clang
SRC_NAME = error.c\
		   exec_command.c\
		   ft_cd.c\
		   ft_echo.c\
		   ft_env.c\
		   ft_unsetenv.c\
		   list_to_tab.c\
		   tab_to_list.c\
		   treatment_builtins.c\
		   main.c\
		   minishell.c\
		   parssing_env.c\
		   setenv.c
SRC_PATH = src
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(SRC:.c=.o)
RM = rm -f

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I includes -I libft/includes -lft -L libft

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@ -I includes -I libft/includes

clean:
	@make -C libft clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C libft fclean
	@$(RM) $(NAME)

re: fclean all
