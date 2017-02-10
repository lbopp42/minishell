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

void	change_oldpwd(t_lst **env, char *buf)
{
	t_lst	*origin;

	origin = *env;
	while (*env && (*env)->next)
	{
		if (!ft_strcmp((*env)->name, "OLDPWD"))
		{
			if ((*env)->content)
				free((*env)->content);
			(*env)->content = ft_strdup(buf);
			break ;
		}
		*env = (*env)->next;
	}
	if (!(*env))
	{
		if (!(*env = (t_lst*)malloc(sizeof(t_lst))))
			return ;
		origin = *env;
		(*env)->name = ft_strdup("OLDPWD");
		(*env)->content = ft_strdup(buf);
		(*env)->next = NULL;
	}
	else if (ft_strcmp((*env)->name, "OLDPWD"))
		ft_setenv(*env, "OLDPWD", buf);
	else if (!ft_strcmp((*env)->name, "OLDPWD") && !(*env)->next)
	{
		if ((*env)->content)
			free((*env)->content);
		(*env)->content = ft_strdup(buf);
	}
	*env = origin;
}

void	change_pwd(t_lst **env)
{
	char	buf[256];
	t_lst	*origin;

	origin = *env;
	ft_bzero(buf, 256);
	getcwd(buf, 256);
	while (*env && (*env)->next)
	{
		if (!ft_strcmp((*env)->name, "PWD"))
		{
			if ((*env)->content)
				free((*env)->content);
			(*env)->content = ft_strdup(buf);
			break ;
		}
		*env = (*env)->next;
	}
	if (!(*env))
	{
		if (!(*env = (t_lst*)malloc(sizeof(t_lst))))
			return ;
		origin = *env;
		(*env)->name = ft_strdup("PWD");
		(*env)->content = ft_strdup(buf);
		(*env)->next = NULL;
	}
	else if (ft_strcmp((*env)->name, "PWD"))
		ft_setenv(*env, "PWD", buf);
	else if (!ft_strcmp((*env)->name, "PWD") && !(*env)->next)
	{
		if ((*env)->content)
			free((*env)->content);
		(*env)->content = ft_strdup(buf);
	}
	(*env) = origin;
}

void	ft_cd(char **array, t_lst **env_lst)
{
	int		ret;
	char	buf[256];

	ret = 0;
	ft_bzero(buf, 256);
	getcwd(buf, 256);
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
			return ;
		}
	}
	if (ret == -1)
		ft_putendstr_fd("cd: no such file or directory: ", array[1], 2);
	else
	{
		if (array[1] && !ft_strcmp(array[1], "-") &&
			get_env_var("OLDPWD", *env_lst))
			ft_putendl(get_env_var("OLDPWD", *env_lst));
		change_pwd(env_lst);
		change_oldpwd(env_lst, buf);
	}
}
