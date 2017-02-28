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

char		*get_path(t_lst *env, char *command)
{
	t_lst	*origin;

	origin = env;
	if (env == NULL)
		return (command);
	while (env != NULL)
	{
		if (!ft_strcmp(env->name, "PATH"))
			break ;
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

static void	launch_execve(char *array[], t_lst *env_lst, char *path)
{
	int		signal;
	pid_t	father;
	char	**env;

	env = list_to_tab(env_lst);
	father = fork();
	if (father > 0)
	{
		wait(&signal);
		if (WIFSIGNALED(signal))
			print_signal(signal);
		del_array(env);
		free(path);
	}
	if (father == 0)
		execve(path, array, env);
}

int			check_path(char *path, char **array)
{
	struct stat st;

	if ((lstat(path, &st) != -1 && !S_ISREG(st.st_mode))
			|| access(path, X_OK) != 0)
	{
		ft_putendstr_fd("minishell: permission denied: ", array[0], 2);
		write(2, "\n", 1);
		return (0);
	}
	return (1);
}

void		exec_command(char *array[], t_lst *env_lst)
{
	char		*path;

	path = NULL;
	if (ft_strchr(array[0], '/') || env_lst == NULL)
	{
		if (access(array[0], F_OK) == 0)
			path = ft_strdup(array[0]);
		else
		{
			ft_putendstr_fd("minishell: command not found: ", array[0], 2);
			write(2, "\n", 1);
			return ;
		}
	}
	path = (!path) ? get_path(env_lst, array[0]) : path;
	if (path)
	{
		if (!check_path(path, array))
		{
			free(path);
			return ;
		}
		launch_execve(array, env_lst, path);
	}
	return ;
}
