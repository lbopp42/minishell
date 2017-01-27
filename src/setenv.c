/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:33:09 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/25 17:00:09 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(t_lst *env, char *var, char *valeur)
{
	if (var == NULL || valeur == NULL)
	{
		ft_putendl_fd("env: too few arguments: env variable value", 2);
		return ;
	}
	while (env->next != NULL)
	{
		if (!ft_strcmp(env->name, var))
		{
			free(env->content);
			env->content = ft_strdup(valeur);
			return ;
		}
		env = env->next;
	}
	if (!ft_strcmp(env->name, var))
	{
		free(env->content);
		env->content = ft_strdup(valeur);
		return ;
	}
	if (!(env->next = (t_lst*)malloc(sizeof(t_lst))))
		return;
	env->next->name = ft_strdup(var);
	env->next->content = ft_strdup(valeur);
	env->next->next = NULL;
}
