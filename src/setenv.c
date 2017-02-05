/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:33:09 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/05 16:00:11 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(t_lst *env, char *var, char *valeur)
{
	t_lst	*tmp;

	tmp = env;
	while (env->next != NULL)
	{
		if (!ft_strcmp(env->name, var))
		{
			free(env->content);
			env->content = ft_strdup(valeur);
			env = tmp;
			return ;
		}
		env = env->next;
	}
	if (!ft_strcmp(env->name, var))
	{
		free(env->content);
		env->content = ft_strdup(valeur);
		env = tmp;
		return ;
	}
	if (!(env->next = (t_lst*)malloc(sizeof(t_lst))))
	{
		env = tmp;
		return ;
	}
	env->next->name = ft_strdup(var);
	env->next->content = ft_strdup(valeur);
	env->next->next = NULL;
	env = tmp;
}
