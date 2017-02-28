/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:47:00 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/28 15:47:01 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_valid_char(int *exec, char *buff, int *sp)
{
	static int	quote = 0;
	char		tmp;

	ft_putchar(buff[0]);
	if (ft_isspace(buff[0]) && sp == 0)
		return ;
	g_line = ft_stradd(g_line, buff);
	if ((tmp = buff[0]) && (tmp == 34 || tmp == 39))
	{
		if (quote == 1)
			quote = 0;
		else
			quote = 1;
	}
	if (quote == 0 && buff[0] == ';')
		*exec = 0;
	*sp = 1;
}

void		treat_char(char *buff, int *sp, t_lst *env_lst)
{
	static int	exec = 0;

	if (ft_isprint(buff[0]) && !buff[1])
		print_valid_char(&exec, buff, sp);
	else if (buff[0] == 9 && !buff[1] && env_lst && ft_isenv(env_lst, "PATH"))
		find_cmd(env_lst, &exec);
	else if (buff[0] == 12 && !buff[1])
	{
		tputs(tgetstr("cl", NULL), 1, &put_my_char);
		write_promptsh();
		ft_putstr(g_line);
	}
	exec = (buff[0] == 10 && !buff[1]) ? 0 : exec;
}

void		get_line(t_lst *env_lst)
{
	char	buff[4];
	int		i;
	int		sp;

	sp = 0;
	if (!(g_line = ft_strnew(1)))
		return ;
	ft_bzero(buff, 4);
	while (buff[0] != 10)
	{
		i = 0;
		ft_bzero(buff, 4);
		read(0, buff, 4);
		treat_char(buff, &sp, env_lst);
	}
	ft_putchar('\n');
}

int			put_my_char(int c)
{
	write(1, &c, 1);
	return (1);
}
