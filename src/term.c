/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 12:38:13 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/25 12:38:15 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_term(void)
{
	char			*term;
	struct termios	attr;
	t_info			*info;

	info = singleton(NULL);
	tcgetattr(STDIN_FILENO, &info->init_term);
	tcgetattr(STDIN_FILENO, &attr);
	singleton(info);
	attr.c_lflag &= ~(ECHO | ICANON);
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &attr);
	if (!(term = getenv("TERM")))
	{
		ft_putstr_fd("minishell: environment not found\n", 2);
		default_term();
		exit(0);
	}
	else
		tgetent(NULL, term);
}

void	default_term(void)
{
	t_info	*info;

	info = singleton(NULL);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &info->init_term);
	tgetent(NULL, getenv("TERM"));
}