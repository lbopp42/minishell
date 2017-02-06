/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 08:53:00 by lbopp             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2017/02/05 15:40:33 by lbopp            ###   ########.fr       */
=======
/*   Updated: 2017/02/03 17:06:49 by lbopp            ###   ########.fr       */
>>>>>>> be5ef8071135ba8211cc105a8cfdd85b6be1ca1e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_oldpwd(t_lst *env, char *buf)
{
	t_lst	*origin;

	origin = env;
	while (env->next != NULL)
	{
		if (!ft_strcmp(env->name, "OLDPWD"))
		{
			if (env->content)
				free(env->content);
			env->content = ft_strdup(buf);
			break ;
		}
		env = env->next;
	}
	if (ft_strcmp(env->name, "OLDPWD"))
	{
		if (!(env->next = (t_lst*)malloc(sizeof(t_lst))))
			return ;
		env->next->name = ft_strdup("OLDPWD");
		env->next->content = ft_strdup(buf);
		env->next->next = NULL;
	}
	env = origin;
}

void	change_pwd(t_lst *env)
{
	char	buf[256];
	t_lst	*origin;

	origin = env;
	ft_bzero(buf, 256);
	getcwd(buf, 256);
	while (env->next != NULL)
	{
		if (!ft_strcmp(env->name, "PWD"))
		{
			if (env->content)
				free(env->content);
			env->content = ft_strdup(buf);
			break ;
		}
		env = env->next;
	}
	if (ft_strcmp(env->name, "PWD"))
	{
		if (!(env->next = (t_lst*)malloc(sizeof(t_lst))))
			return ;
		env->next->name = ft_strdup("PWD");
		env->next->content = ft_strdup(buf);
		env->next->next = NULL;
	}
	env = origin;
}

<<<<<<< HEAD
void	ft_cd(char **array, t_lst *env_lst)
=======
#include <stdio.h>

void	ft_cd(char **array, char **env[])
>>>>>>> be5ef8071135ba8211cc105a8cfdd85b6be1ca1e
{
	int		ret;
	char	buf[256];
<<<<<<< HEAD
	t_lst	*origin;
=======
	char	*path;
>>>>>>> be5ef8071135ba8211cc105a8cfdd85b6be1ca1e

	origin = env_lst;
	ret = 0;
<<<<<<< HEAD
=======
	path = NULL;
	env_lst = tab_to_list(*env);
>>>>>>> be5ef8071135ba8211cc105a8cfdd85b6be1ca1e
	ft_bzero(buf, 256);
	getcwd(buf, 256);
	if (array[1] && ft_strcmp(array[1], "-"))
	{
		printf("ICI\n");
		ret = chdir(array[1]);
	}
	else
<<<<<<< HEAD
		if (get_env_var("$HOME", env_lst))
		{
			ret = chdir(get_env_var("$HOME", env_lst));
			if (ret != -1)
			{
				change_pwd(env_lst);
				change_oldpwd(env_lst, buf);
			}
		}
	if (ret == -1)
=======
	{
		if (array[1] && !ft_strcmp(array[1], "-"))
			path = get_env_var("$OLDPWD", *env);
		else
			path = get_env_var("$HOME", *env);
		ret = chdir(path);
	}
	if (ret != -1)
	{
		change_pwd(env_lst);
		change_oldpwd(env_lst, buf);
		if (array[1] && !ft_strcmp(array[1], "-"))
			ft_putendl(get_env_var("$OLDPWD", *env));
	}
	else
>>>>>>> be5ef8071135ba8211cc105a8cfdd85b6be1ca1e
	{
		ft_putstr("cd: no such file or directory: ");
		path = path ? path : array[1];
		ft_putendl(path);
	}
<<<<<<< HEAD
	env_lst = origin;
=======
	*env = list_to_tab(env_lst);
	del_lst(env_lst);
>>>>>>> be5ef8071135ba8211cc105a8cfdd85b6be1ca1e
}
