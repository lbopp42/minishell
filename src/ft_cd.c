/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 08:53:00 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/28 17:08:30 by lbopp            ###   ########.fr       */
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
}

void	ft_cd(char **array, char **env[])
{
	int		ret;
	t_lst	*env_lst;
	char	buf[256];

	ret = 0;
	env_lst = tab_to_list(*env);
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
		if (get_env_var("$HOME", *env))
		{
			ret = chdir(get_env_var("$HOME", *env));
			if (ret != -1)
			{
				change_pwd(env_lst);
				change_oldpwd(env_lst, buf);
			}
		}
	*env = list_to_tab(env_lst);
	del_lst(env_lst);
	if (ret == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(array[1]);
	}
}
