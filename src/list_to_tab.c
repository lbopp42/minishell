/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:45:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/02 11:17:19 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_lst(t_lst *lst, char **array)
{
	int	i;
	int	j;
	int	k;

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
		array[i][j + 1 + k] = '\0';
		i++;
		lst = lst->next;
	}
	return (array);
}

void	create_line(t_lst *lst, char ***array)
{
	int	size;
	int	i;

	i = 0;
	while (lst != NULL)
	{
		size = ft_strlen(lst->name) + ft_strlen(lst->content) + 1;
		if (!((*array)[i] = (char*)malloc(sizeof(char) * size + 1)))
			return ;
		i++;
		lst = lst->next;
	}
}

int		lst_size(t_lst *lst)
{
	int size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char	**list_to_tab(t_lst *lst)
{
	char	**array;
	t_lst	*origin;
	int		size;

	origin = lst;
	array = NULL;
	size = lst_size(lst);
	if (!(array = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	array[size] = NULL;
	create_line(lst, &array);
	lst = origin;
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
