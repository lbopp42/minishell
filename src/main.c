/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:04:19 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/07 15:20:58 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		get_line(char **line, t_lst *env_lst)
{
	char	buff[4];
	int		i;
	int		sp;

	sp = 0;
	if (!(*line = ft_strnew(1)))
		return ;
	ft_bzero(buff, 4);
	while (buff[0] != 10)
	{
		i = 0;
		ft_bzero(buff, 4);
		read(0, buff, 4);
		if (ft_isprint(buff[0]) && !buff[1])
		{
			ft_putchar(buff[0]);
			if (ft_isspace(buff[0]) && sp == 0)
				continue ;
			*line = ft_stradd(*line, buff);
			sp = 1;
		}
		else if (buff[0] == 9 && !buff[1])
			find_cmd(line, env_lst);
	}
	ft_putchar('\n');
}

int			put_my_char(int c)
{
	write(1, &c, 1);
	return (1);
}

static void	launch_minishell(t_lst **env_lst, char **last_line)
{
	char		*line;

	line = NULL;
	manage_signal();
	write_promptsh();
	get_line(&line, *env_lst);
	if (line && line[0])
	{
		parssing_line(&line, *env_lst, *last_line);
		(*last_line) ? free(*last_line) : 0;
		*last_line = ft_strdup(line);
		minishell(env_lst, last_line, line);
	}
	free(line);
}

int			main(void)
{
	t_lst		*env_lst;
	char		*last_line;
	extern char	**environ;

	last_line = NULL;
	init_term();
	env_lst = tab_to_list(environ);
	while (42)
		launch_minishell(&env_lst, &last_line);
	del_lst(env_lst);
	return (1);
}
