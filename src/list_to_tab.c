/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:45:55 by lbopp             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2017/02/06 10:50:09 by lbopp            ###   ########.fr       */
=======
/*   Updated: 2017/02/03 17:01:22 by lbopp            ###   ########.fr       */
>>>>>>> be5ef8071135ba8211cc105a8cfdd85b6be1ca1e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_lst(t_lst *lst, char ***array)
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
			(*array)[i][j] = lst->name[j];
			j++;
		}
		(*array)[i][j] = '=';
		while (lst->content[k])
		{
			(*array)[i][j + 1 + k] = lst->content[k];
			k++;
		}
		i++;
		lst = lst->next;
	}
<<<<<<< HEAD
	lst = origin;
	return (array);
=======
>>>>>>> be5ef8071135ba8211cc105a8cfdd85b6be1ca1e
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
<<<<<<< HEAD
	size = lst_size(lst) + 2;
	if (!(array = (char**)ft_memalloc(sizeof(char*) * size)))
		return (NULL);
	create_line(lst, &array);
	array = fill_lst(lst, array);
=======
	size = lst_size(lst);
	if (!(array = (char**)ft_memalloc(sizeof(char*) * (size + 1))))
		return (NULL);
	create_line(lst, &array);
	lst = origin;
	fill_lst(lst, &array);
>>>>>>> be5ef8071135ba8211cc105a8cfdd85b6be1ca1e
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
	free(array[i]);
	free(array);
}
