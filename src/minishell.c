/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:09:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/09 09:23:57 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handle(int signal)
{
	int	prompt;

	prompt = singleton_prompt(0);
	if (signal == SIGINT)
	{
		if (prompt == 1)
			write_promptsh();
		signal = 0;
		g_line = NULL;
		g_line = ft_strnew(1);
	}
	return ;
}

void	clean_up(char *last_line, char ***command, char **array)
{
	free(last_line);
	free(g_line);
	del_array(*command);
	*command = NULL;
	del_array(array);
	ft_exit();
}

void	minishell(t_lst **env_lst, char **last_line)
{
	char		**command;
	char		**array;
	int			i;
	const char	*array_cmd[] =
	{"cd", "exit", "setenv", "unsetenv", "env", "echo", NULL};

	array = NULL;
	command = NULL;
	array = ft_strsplitquote(g_line, ';');
	i = 0;
	while (array && array[i])
	{
		command = ft_whitespaces(array[i]);
		if (command && treatment_builtins(command, env_lst) == 0)
		{
			del_lst(*env_lst);
			clean_up(*last_line, &command, array);
		}
		else if (command && !ft_isinarray(command[0], (char**)array_cmd))
			exec_command(command, *env_lst);
		del_array(command);
		i++;
	}
	del_array(array);
}
