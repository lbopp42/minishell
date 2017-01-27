/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 12:39:49 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/25 14:58:39 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void	create_lst(t_lst **lst, char *array)
{
	if (!(*lst = (t_lst*)malloc(sizeof(t_lst))))
		return;
	(*lst)->name = ft_strcdup(array, '=');
	(*lst)->content = ft_strchr(array, '=') + 1;
	(*lst)->next = NULL;
}

void	add_lst(t_lst **lst, char *array)
{
	if (*lst == NULL)
		create_lst(lst, array);
	else
		add_lst(&((*lst)->next), array);
}

void	tab_to_list(char *array[], t_lst **lst)
{
	int		i;

	*lst = NULL;
	i = 0;
	while (array[i])
	{
		add_lst(lst, array[i]);
		i++;
	}
}
