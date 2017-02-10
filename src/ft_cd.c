/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 08:53:00 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/08 09:59:49 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		treat_cd(char **array, t_lst **env_lst, int ret)
{
	if (array[1])
	{
		if (!ft_strcmp(array[1], "-"))
		{
			if (get_env_var("OLDPWD", *env_lst))
				ret = chdir(get_env_var("OLDPWD", *env_lst));
			else
				ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		}
		else
			ret = chdir(array[1]);
	}
	else
	{
		if (get_env_var("HOME", *env_lst))
			ret = chdir(get_env_var("HOME", *env_lst));
		else
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (0);
		}
	}
	return (1);
}

void	ft_cd(char **array, t_lst **env_lst)
{
	int		ret;
	char	buf[256];
	char	path[256];

	ret = 0;
	ft_bzero(buf, 256);
	ft_bzero(path, 256);
	getcwd(buf, 256);
	if (!treat_cd(array, env_lst, ret))
		return ;
	if (ret == -1)
		ft_putendstr_fd("cd: no such file or directory: ", array[1], 2);
	else
	{
		if (array[1] && !ft_strcmp(array[1], "-") &&
				get_env_var("OLDPWD", *env_lst))
			ft_putendl(get_env_var("OLDPWD", *env_lst));
		getcwd(path, 256);
		ft_setenv(env_lst, "PWD", path);
		ft_setenv(env_lst, "OLDPWD", buf);
	}
}
