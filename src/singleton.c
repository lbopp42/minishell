/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 12:44:48 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/25 12:44:50 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*singleton(t_info *data)
{
	t_info	*info;

	info = NULL;
	if (data)
		info = data;
	return (info);
}

void	init_sigleton(void)
{
	t_info	*info;

	if (!(info = (t_info*)ft_memalloc(sizeof(t_info))))
		return ;
	info = singleton(info);
}