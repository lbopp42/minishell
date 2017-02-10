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

void	fill_env(t_lst **env, char *var, char *valeur)
{
	t_lst	*tmp;

	tmp = *env;
	if (!tmp)
	{
		if (!(*env = (t_lst*)malloc(sizeof(t_lst))))
			return ;
		(*env)->name = ft_strdup(var);
		(*env)->content = ft_strdup(valeur);
		(*env)->next = NULL;
	}
	else
	{
		if (!(tmp->next = (t_lst*)malloc(sizeof(t_lst))))
			return ;
		tmp->next->name = ft_strdup(var);
		tmp->next->content = ft_strdup(valeur);
		tmp->next->next = NULL;
	}
}

void	ft_setenv(t_lst **env, char *var, char *valeur)
{
	t_lst	*tmp;

	tmp = *env;
	while (tmp && tmp->next != NULL)
	{
		if (!ft_strcmp(tmp->name, var))
		{
			free(tmp->content);
			tmp->content = ft_strdup(valeur);
			return ;
		}
		tmp = tmp->next;
	}
	if (tmp && !ft_strcmp(tmp->name, var))
	{
		free(tmp->content);
		tmp->content = ft_strdup(valeur);
		return ;
	}
	fill_env(env, var, valeur);
}
