# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/02 11:07:10 by lbopp             #+#    #+#              #
#    Updated: 2017/02/26 10:02:50 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/
CC = clang
SRC_NAME = completion.c\
		   error.c\
		   exec_command.c\
		   ft_cd.c\
		   ft_echo.c\
		   ft_env.c\
		   ft_exit.c\
		   ft_unsetenv.c\
		   list_to_tab.c\
		   tab_to_list.c\
		   treatment_builtins.c\
		   main.c\
		   minishell.c\
		   parssing_env.c\
		   prompt.c\
		   setenv.c\
		   signal.c\
		   singleton.c\
		   term.c\
		   verif_access.c
SRC_PATH = src
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(SRC:.c=.o)
RM = rm -f

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I includes -I libft/includes -lft -L libft -ltermcap

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@ -I includes -I libft/includes

clean:
	@make -C libft clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C libft fclean
	@$(RM) $(NAME)

re: fclean all
