/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 10:30:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/06 10:39:10 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_lst *env, char *command)
{
	char	*path;
	char	**array;
	int		ret;
	t_lst	*origin;
	int		i;

	origin = env;
	if (env == NULL)
		return(command);
	while (env != NULL)
	{
		if (!ft_strcmp(env->name, "PATH"))
			break;
		env = env->next;
	}
	array = ft_strsplit(env->content, ':');
	i = 0;
	while (array[i])
	{
		path = ft_strdup(array[i]);
		path = ft_stradd(path, "/");
		path = ft_stradd(path, command);
		if ((ret = access(path, F_OK)) == 0)
			break;
		free(path);
		path = NULL;
		i++;
	}
	del_array(array);
	if (ret != 0)
	{
		ft_putendstr_fd("minishell: command not found: ", command, 2);
		write(2, "\n", 1);
	}
	return (path);
}

void	exec_command(char *array[], t_lst *env_lst)
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
