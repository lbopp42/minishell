/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:09:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/27 10:52:27 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(int ac, char *av[], char *env[])
{
	char	*line;
	char	**array;

	write(1, "$> ", 3);
	get_next_line(0, &line);
	array = ft_whitespaces(line); //TODO free this array
	if (array[0] == NULL)
		minishell(ac, av, env);
	else if (array[0] != NULL && treatment_builtins(array, env) == 1)
		minishell(ac, av, env);
	else if (array[0] != NULL && treatment_builtins(array, env) == 0)
		exit(EXIT_SUCCESS);
	else
		exec_command(array, ac, av, env);
}
