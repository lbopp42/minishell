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
	(void)signal;
	if (signal == SIGINT)
		write_promptsh();
	return ;
}

void	clean_up(char *last_line, char *line, char ***command, char **array)
{
	free(last_line);
	free(line);
	del_array(*command);
	*command = NULL;
	del_array(array);
	ft_exit();
}

void	minishell(t_lst **env_lst, char **last_line, char *line)
{
	char		**command;
	char		**array;
	int			i;
	const char	*tab[] =
	{"cd", "exit", "setenv", "unsetenv", "env", "echo", NULL};

	array = NULL;
	array = ft_strsplitquote(line, ';');
	i = 0;
	while (array[i])
	{
		command = ft_whitespaces(array[i]);
		if (command && treatment_builtins(command, env_lst) == 0)
		{
			del_lst(*env_lst);
			clean_up(*last_line, line, &command, array);
		}
		else if (command && !ft_isinarray(command[0], (char**)tab))
			exec_command(command, *env_lst);
		del_array(command);
		i++;
	}
	del_array(array);
}
