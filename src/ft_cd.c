/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 08:53:00 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/05 15:40:33 by lbopp            ###   ########.fr       */
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

void	ft_cd(char **array, t_lst *env_lst)
{
	int		ret;
	char	buf[256];
	t_lst	*origin;

	origin = env_lst;
	ret = 0;
	ft_bzero(buf, 256);
	getcwd(buf, 256);
	if (array[1])
	{
		ret = chdir(array[1]);
		if (ret != -1)
		{
			change_pwd(env_lst);
			change_oldpwd(env_lst, buf);
		}
	}
	else
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
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(array[1]);
	}
	env_lst = origin;
}
