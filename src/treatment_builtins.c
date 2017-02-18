/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:38:40 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/08 10:07:35 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treatment_builtins(char *array[], t_lst **env_lst)
{
	if (array[0] && !ft_strcmp(array[0], "cd"))
		ft_cd(array, env_lst);
	else if (array[0] && !ft_strcmp(array[0], "echo"))
		ft_echo(array);
	else if (array[0] && !ft_strcmp(array[0], "exit"))
		return (0);
	else if (array[0] && !ft_strcmp(array[0], "setenv"))
	{
		if ((array[1] == NULL || array[2] == NULL) && !error_arg_env())
			return (1);
		ft_setenv(env_lst, array[1], array[2]);
	}
	else if (array[0] && !ft_strcmp(array[0], "unsetenv"))
		ft_unsetenv(*env_lst, array[1]);
	else if (array[0] && !ft_strcmp(array[0], "env"))
		ft_env(*env_lst);
	else
		return (2);
	return (1);
}
