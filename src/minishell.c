/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:09:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/05 17:01:58 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handle(int signal)
{
	(void)signal;
	return ;
}

void	minishell(t_lst *env_lst)
{
	char	*line;
	char	**command;
	char	**array;
	int		i;

	line = NULL;
	array = NULL;
	while (42)
	{
		signal(SIGINT, signal_handle);
		write(1, "$> ", 3);
		get_next_line(0, &line);
		if (!line[0])
		{
			free(line);
			continue ;
		}
		array = ft_strsplitquote(line, ';');
		free(line);
		i = 0;
		while (array[i])
		{
			command = ft_whitespaces(array[i]);
			command = parssing_var(command, env_lst);
			if (command && treatment_builtins(command, env_lst) == 1) //Maybe del a if
			{
				del_array(command);
				i++;
				continue ;
			}
			else if (command && treatment_builtins(command, env_lst) == 0)
			{
				//del_lst(env_lst);
				exit(EXIT_SUCCESS);
			}
			else
				exec_command(command, env_lst);
			del_array(command);
			i++;
		}
		del_array(array);
	}
}
