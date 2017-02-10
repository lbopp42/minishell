/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:31:45 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/10 14:57:07 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv(t_lst *env, char *var)
{
	t_lst	*tmp;
	t_lst	*origin;

	origin = env;
	if (!var || !ft_isenv(env, var))
	{
		if (!var)
			ft_putendl_fd("unsetenv: Too few arguments.", 2);
		return ;
	}
	tmp = origin;
	while (origin != NULL)
	{
		if (!ft_strcmp(origin->name, var))
		{
			free(origin->name);
			free(origin->content);
			if (tmp != NULL)
				tmp->next = origin->next;
			free(origin);
			return ;
		}
		tmp = origin;
		origin = origin->next;
	}
}
