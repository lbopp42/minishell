/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:33:09 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/27 14:38:38 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*ft_setenv(t_lst *env, char *var, char *valeur)
{
	t_lst	*tmp;

	tmp = env;
	if (var == NULL || valeur == NULL)
	{
		ft_putendl_fd("env: too few arguments: env variable value", 2);
		return (NULL);
	}
	while (env->next != NULL)
	{
		if (!ft_strcmp(env->name, var))
		{
			free(env->content);
			env->content = ft_strdup(valeur);
			return (NULL);
		}
		env = env->next;
	}
	if (!ft_strcmp(env->name, var))
	{
		free(env->content);
		env->content = ft_strdup(valeur);
		return (NULL);
	}
	if (!(env->next = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	env->next->name = ft_strdup(var);
	env->next->content = ft_strdup(valeur);
	env->next->next = NULL;
	return (tmp);
}
