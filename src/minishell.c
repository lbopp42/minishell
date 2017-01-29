/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:09:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/29 16:56:47 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(int ac, char *av[], char *env[])
{
	char	*line;
	char	**array;

	line = NULL;
	array = NULL;
	write(1, "$> ", 3);
	get_next_line(0, &line);
	if (!line[0])
		minishell(ac, av, env);
	else
	{
		array = ft_whitespaces(line);
		free(line);
		array = parssing_var(array, env);
		if (array[0] != NULL && treatment_builtins(array, &env) == 1)
			minishell(ac, av, env);
		else if (array[0] != NULL && treatment_builtins(array, &env) == 0)
			exit(EXIT_SUCCESS);
		else
			exec_command(array, ac, av, env);
	}
}
