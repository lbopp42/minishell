/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:09:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/30 17:22:18 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handle(int signal)
{
	(void)signal;
	return ;
}

void	minishell(int ac, char *av[], char *env[])
{
	char	*line;
	char	**array;

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
		array = ft_whitespaces(line);
		free(line);
		array = parssing_var(array, env);
		if (array && treatment_builtins(array, &env) == 1)
		{
			del_array(array);
			continue ;
		}
		else if (array && treatment_builtins(array, &env) == 0)
			exit(EXIT_SUCCESS);
		else
			exec_command(array, ac, av, env);
	}
}
