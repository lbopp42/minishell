/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:09:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/02 13:19:57 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handle(int signal)
{
	(void)signal;
	return ;
}

void	minishell(char *env[])
{
	char	*line;
	char	**command;
	char	**array;
	int		i;

	i = 0;
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
		while (array[i])
		{
			command = ft_whitespaces(array[i]);
			command = parssing_var(command, env);
			if (command && treatment_builtins(command, &env) == 1)
			{
				del_array(command);
				i++;
				continue ;
			}
			else if (command && treatment_builtins(command, &env) == 0)
				exit(EXIT_SUCCESS);
			else
				exec_command(command, env);
			i++;
		}
		del_array(array);
	}
}
