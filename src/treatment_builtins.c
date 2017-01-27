/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:38:40 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/27 15:23:02 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treatment_builtins(char *array[], char **env[])
{
	t_lst	*lst;

	lst = NULL;
	if (!ft_strcmp(array[0], "cd"))
		ft_cd(array, *env);
	else if (!ft_strcmp(array[0], "echo"))
		ft_echo(array);
	else if (!ft_strcmp(array[0], "exit"))
		return (0);
	else if (!ft_strcmp(array[0], "setenv"))
	{
		lst = tab_to_list(*env); //TODO free this lst
		lst = ft_setenv(lst, array[1], array[2]);
		*env = list_to_tab(lst);
		del_lst(lst);
	}
	else if (!ft_strcmp(array[0], "unsetenv"))
	{
		lst = tab_to_list(*env); //TODO free this lst
		ft_unsetenv(lst, array[1]);
		*env = list_to_tab(lst);
		del_lst(lst);
	}
	else if (!ft_strcmp(array[0], "env"))
		ft_env(*env);
	else
		return (2);
	return (1);
}
