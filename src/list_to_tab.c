/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:45:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/06 10:50:09 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_lst(t_lst *lst, char **array)
{
	int		i;
	int		j;
	int		k;
	t_lst	*origin;

	origin = lst;
	i = 0;
	while (lst != NULL)
	{
		j = 0;
		k = 0;
		while (lst->name[j])
		{
			array[i][j] = lst->name[j];
			j++;
		}
		array[i][j] = '=';
		while (lst->content[k])
		{
			array[i][j + 1 + k] = lst->content[k];
			k++;
		}
		i++;
		lst = lst->next;
	}
	lst = origin;
	return (array);
}

void	create_line(t_lst *lst, char ***array)
{
	int		size;
	int		i;
	t_lst	*origin;

	i = 0;
	origin = lst;
	while (lst != NULL)
	{
		size = ft_strlen(lst->name) + ft_strlen(lst->content) + 1;
		if (!((*array)[i] = (char*)ft_memalloc(size + 1)))
			return ;
		i++;
		lst = lst->next;
	}
	lst = origin;
}

int		lst_size(t_lst *lst)
{
	int		size;
	t_lst	*origin;

	origin = lst;
	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	lst = origin;
	return (size);
}

char	**list_to_tab(t_lst *lst)
{
	char	**array;
	int		size;

	array = NULL;
	size = lst_size(lst) + 2;
	if (!(array = (char**)ft_memalloc(sizeof(char*) * size)))
		return (NULL);
	create_line(lst, &array);
	array = fill_lst(lst, array);
	return (array);
}

void	del_array(char *array[])
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
