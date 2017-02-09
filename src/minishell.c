/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:09:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/09 09:23:57 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handle(int signal)
{
	(void)signal;
	if (signal == SIGINT)
		write_promptsh();
	return ;
}

void	minishell(t_lst **env_lst)
{
	char	*line;
	char	**command;
	char	**array;
	int		i;
	char	*last_line;

	line = NULL;
	array = NULL;
	last_line = NULL;
	while (42)
	{
		signal(SIGINT, signal_handle);
		signal(SIGQUIT, signal_handle);
		write_promptsh();
		get_next_line(0, &line);
		if (!line[0])
		{
			free(line);
			continue ;
		}
		if (!ft_strcmp(line, "exit"))
			exit(EXIT_SUCCESS);
		parssing_line(&line, *env_lst, last_line);
		array = ft_strsplitquote(line, ';');
		i = 0;
		while (array[i])
		{
			command = ft_whitespaces(array[i]);
			if (last_line)
				free(last_line);
			last_line = ft_strdup(line);
			if (command && treatment_builtins(command, env_lst) == 1) //Maybe del a if
			{
				del_array(command);
				i++;
				continue ;
			}
			else if (command && treatment_builtins(command, env_lst) == 0)
			{
				free(last_line);
				free(line);
				del_array(command);
				del_array(array);
				del_lst(*env_lst);
				exit(EXIT_SUCCESS);
			}
			else
				exec_command(command, *env_lst);
			del_array(command);
			i++;
		}
		free(line);
		del_array(array);
	}
}
