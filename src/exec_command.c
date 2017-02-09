/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 10:30:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/08 12:34:20 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*verif_access(t_lst *env, char *command)
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
				break;
		free(path);
		path = NULL;
	}
	del_array(array);
	if (!path)
	{
		if (ret == -1)
			ft_putendstr_fd("minishell: permission denied: ", command, 2);
		else
			ft_putendstr_fd("minishell: command not found: ", command, 2);
		write(2, "\n", 1);
	}
	return (path);
}

char		*get_path(t_lst *env, char *command)
{
	t_lst	*origin;

	origin = env;
	if (env == NULL)
		return(command);
	while (env != NULL)
	{
		if (!ft_strcmp(env->name, "PATH"))
			break;
		env = env->next;
	}
	if (env)
		return (verif_access(env, command));
	else
	{
		ft_putendstr_fd("minishell: No such file or directory: ", command, 2);
		write(2, "\n", 1);
	}
	return (NULL);
}

void		exec_command(char *array[], t_lst *env_lst)
{
	char	*path;
	int		signal;
	pid_t	father;
	int		erreur;
	char	**env;

	erreur = 0;
	path = NULL;
	if (ft_strchr(array[0], '/') || env_lst == NULL)
	{
		if (access(array[0], F_OK) == 0)
			path = ft_strdup(array[0]);
		else
		{
			erreur = 1;
			ft_putendstr_fd("minishell: command not found: ", array[0], 2);
			write(2, "\n", 1);
			return ;
		}
	}
	if (!path)
		path = get_path(env_lst, array[0]);
	if (path)
	{
		env = list_to_tab(env_lst);
		father = fork();
		if (father > 0)
		{
			wait(&signal);
			if (WIFSIGNALED(signal))
				print_signal(signal);
			del_array(env);
			free(path);
			return ;
		}
		if (father == 0)
			execve(path, array, env);
	}
	return;
}
