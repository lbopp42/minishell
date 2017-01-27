/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 10:30:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/27 13:21:30 by lbopp            ###   ########.fr       */
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

void	exec_command(char *array[], int ac, char *av[], char *env[])
{
	char	*path;
	int		signal;
	pid_t	father;

	path = NULL;
	if (ft_strchr(array[0], '/') || env[0] == NULL)
	{
		if (access(array[0], F_OK) == 0)
			path = ft_strdup(array[0]);
		else
		{
			ft_putendstr_fd("minishell: command not found: ", array[0], 2);
			write(2, "\n", 1);
		}
	}
	father = fork();
	if (father > 0)
	{
		wait(&signal);
		minishell(ac, av, env);
	}
	if (father == 0)
	{
		if (path)
			execve(path, array, env);
		else
			execve(get_path(env, array[0]), array, env);
	}
}
