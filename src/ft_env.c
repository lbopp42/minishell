/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:04:27 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/05 15:49:23 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_lst *env)
{
	t_lst	*origin;

	origin = env;
	while (env != NULL)
	{
		ft_putendch(env->name, '=');
		ft_putendl(env->content);
		env = env->next;
	}
	env = origin;
}
