/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:31:45 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/27 16:43:48 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void	ft_unsetenv(t_lst *env, char *name)
{
	t_lst *tmp;

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
}
