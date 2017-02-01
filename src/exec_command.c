/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 10:30:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/01 09:14:57 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
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

char	*get_path(char *env[], char *command)
{
	int		i;
	char	*path;
	char	**array;
	int		ret;

	i = 0;
	if (env == NULL)
		return(command);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			break;
		i++;
	}
	path = ft_strdup(ft_strchr(env[i], '=') + 1);
	array = ft_strsplit(path, ':');
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
	free_array(array);
	if (ret != 0)
	{
		ft_putendstr_fd("minishell: command not found: ", command, 2);
		write(2, "\n", 1);
	}
	return (path);
}

void	exec_command(char *array[], char *env[])
{
	char	*path;
	int		signal;
	pid_t	father;
	int		erreur;

	erreur = 0;
	path = NULL;
	if (ft_strchr(array[0], '/') || env[0] == NULL)
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
	if (path == NULL)
		path = get_path(env, array[0]);
	if (path != NULL)
	{
		father = fork();
		if (father > 0)
		{
			wait(&signal);
			if (WIFSIGNALED(signal))
				print_signal(signal);
			return ;
		}
		if (father == 0)
			execve(path, array, env);
	}
	return;
}
