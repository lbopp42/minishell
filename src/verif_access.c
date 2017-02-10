/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 13:33:08 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/10 13:33:11 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_no_path(int ret, char *command)
{
	if (ret == -1)
		ft_putendstr_fd("minishell: permission denied: ", command, 2);
	else
		ft_putendstr_fd("minishell: command not found: ", command, 2);
	write(2, "\n", 1);
}

char		*verif_access(t_lst *env, char *command)
{
	char			**array;
	static int		i;
	char			*path;
	int				ret;

	array = ft_strsplit(env->content, ':');
	i = 0;
	ret = 1;
	while (array[i])
	{
		path = ft_strdup(array[i++]);
		path = ft_addslash(path, command);
		if (access(path, F_OK) == 0)
			if ((ret = access(path, X_OK)) == 0)
				break ;
		free(path);
		path = NULL;
	}
	del_array(array);
	if (!path)
		err_no_path(ret, command);
	return (path);
}
