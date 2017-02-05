/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:31:45 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/05 15:43:43 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void	ft_unsetenv(t_lst *env, char *name)
{
	t_lst	*tmp;
	t_lst	*origin;

	origin = env;
	tmp = NULL;
	tmp = env;
	while (env != NULL)
	{
		if (!ft_strcmp(env->name, name))
		{
			free(env->name);
			free(env->content);
			if (tmp != NULL)
				tmp->next = env->next;
			free(env);
			return ;
		}
		tmp = env;
		env = env->next;
	}
	env = origin;
}
