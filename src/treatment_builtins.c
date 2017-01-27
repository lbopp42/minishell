/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:38:40 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/27 10:55:36 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treatment_builtins(char *array[], char *env[])
{
	t_lst	*lst;

	if (!ft_strcmp(array[0], "cd"))
		ft_cd(array, env);
	else if (!ft_strcmp(array[0], "echo"))
		ft_echo(array);
	else if (!ft_strcmp(array[0], "exit"))
		return (0);
	else if (!ft_strcmp(array[0], "setenv"))
	{
		tab_to_list(env, &lst); //TODO free this lst
		ft_setenv(lst, array[1], array[2]);
		env = list_to_tab(lst);
	}
	else if (!ft_strcmp(array[0], "unsetenv"))
	{
		tab_to_list(env, &lst); //TODO free this lst
		ft_unsetenv(lst, array[1]);
		env = list_to_tab(lst);
	}
	else if (!ft_strcmp(array[0], "env"))
		ft_env(env);
	else
		return (2); // 2 = aucun builtin
	return (1); // 1 = 
}
