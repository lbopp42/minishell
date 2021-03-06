/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 10:00:54 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/26 10:00:55 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(char *word, char *cmd)
{
	int	i;

	i = ft_strlen(word);
	g_line = ft_stradd(g_line, &(cmd[i]));
	while (cmd[i])
	{
		ft_putchar(cmd[i]);
		i++;
	}
	ft_putchar(' ');
	g_line = ft_stradd(g_line, " ");
}

char	**extract_exec(char *word, char **array_path)
{
	int				i;
	DIR				*dir;
	struct dirent	*readding;
	char			**exec_array;

	i = 0;
	exec_array = NULL;
	while (array_path && array_path[i])
	{
		if (!(dir = opendir(array_path[i++])))
			continue ;
		while ((readding = readdir(dir)))
		{
			if (!ft_strncmp(readding->d_name, word, ft_strlen(word)) &&
				readding->d_name[0] != '.')
				exec_array = put_exec_in_array(readding->d_name, exec_array);
		}
		closedir(dir);
	}
	return (exec_array);
}

int		browse_path(char *word, t_lst *env_lst)
{
	char	**exec_array;
	char	**array_path;

	exec_array = NULL;
	array_path = NULL;
	array_path = ft_strsplit(get_env_var("PATH", env_lst), ':');
	exec_array = extract_exec(word, array_path);
	del_array(array_path);
	exec_array = add_builtins_in_array(word, exec_array);
	if (exec_array && ft_arraylen(exec_array) == 1)
	{
		print_cmd(word, exec_array[0]);
		del_array(exec_array);
		return (0);
	}
	else
	{
		ft_putchar('\n');
		print_array(exec_array);
		exec_array ? del_array(exec_array) : 0;
		return (1);
	}
}

void	find_cmd(t_lst *env_lst, int *exec)
{
	char	*word;
	char	*tmp;

	word = NULL;
	if (ft_strrchr(g_line, ';') || !ft_strrchr(g_line, ' '))
	{
		if (ft_strrchr(g_line, ';') && !*exec)
			word = ft_strtrim(ft_strrchr(g_line, ';') + 1);
		else if (!*exec)
		{
			tmp = ft_strdup(g_line);
			word = ft_strtrim(tmp);
			free(tmp);
		}
		if (browse_path(word, env_lst) && !*exec)
		{
			write_promptsh();
			ft_putstr(g_line);
		}
		else
			*exec = 1;
		free(word);
	}
	else
		word = ft_strrchr(g_line, ' ') + 1;
}
