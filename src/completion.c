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

char	**cpy_array_in_array(char **src)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = NULL;
	if (!(new_array =
		(char**)ft_memalloc(sizeof(char*) * (ft_arraylen(src) + 2))))
		return (NULL);
	while (src && src[i])
	{
		new_array[i] = ft_strdup(src[i]);
		i++;
	}
	return (new_array);
}

char	**put_exec_in_array(char *exec_name, char **exec_array)
{
	char	**new_array;
	int		i;

	i = 0;
	if (!exec_array)
	{
		if (!(exec_array = (char**)ft_memalloc(sizeof(char*) * 2)))
			return (NULL);
		exec_array[0] = ft_strdup(exec_name);
		return (exec_array);
	}
	if (ft_isinarray(exec_name, exec_array))
		return (exec_array);
	else
	{
		new_array = cpy_array_in_array(exec_array);
		new_array[ft_arraylen(exec_array)] = ft_strdup(exec_name);
		return (new_array);
	}
}

/*
** Management of builtins
*/

char	**add_builtins_in_array(char *exec_name, char **exec_array)
{
	const char	*buil_array[6] = {"echo", "cd", "setenv", "unsetenv", "env",
								"exit"};
	int			i;
	char		**new_array;

	i = 0;
	new_array = NULL;
	if (exec_array)
		new_array = cpy_array_in_array(exec_array);
	while (i < 6)
	{
		if (!ft_strncmp(buil_array[i], exec_name, ft_strlen(exec_name)))
			new_array = put_exec_in_array((char*)buil_array[i], new_array);
		/*else if (!ft_strncmp(buil_array[i], exec_name, ft_strlen(exec_name)))
			new_array = put_exec_in_array((char*)buil_array[i], new_array);*/
		i++;
	}
	return (new_array);
}

void	print_array(char **array)
{
	int				i;
	int				col;
	struct winsize	w;

	i = 0;
	col = 0;
	ioctl(0, TIOCGWINSZ, &w);
	while (array && array[i])
	{
		if ((col + ft_strlen(array[i]) + 1) > w.ws_col)
		{
			col = 0;
			ft_putchar('\n');
		}
		col += ft_strlen(array[i]) + 1;
		ft_putendsp(array[i]);
		i++;
	}
}

void	print_cmd(char *word, char *cmd, char **line)
{
	int	i;

	i = ft_strlen(word);
	*line = ft_stradd(*line, &(cmd[i]));
	while (cmd[i])
	{
		ft_putchar(cmd[i]);
		i++;
	}
	ft_putchar(' ');
	*line = ft_stradd(*line, " ");
}

int		browse_path(char *word, t_lst *env_lst, char **line)
{
	DIR				*dir;
	char			**array_path;
	struct dirent	*readding;
	int				i;
	char			**exec_array;

	i = 0;
	exec_array = NULL;
	(void)word;
	array_path = ft_strsplit(get_env_var("PATH", env_lst), ':');
	while (array_path[i])
	{
		if (!(dir = opendir(array_path[i++])))
			continue ;
		while ((readding = readdir(dir)))
		{
			if (!ft_strncmp(readding->d_name, word, ft_strlen(word)))
				exec_array = put_exec_in_array(readding->d_name, exec_array);
		}
		closedir(dir);
	}
	exec_array = add_builtins_in_array(word, exec_array);
	if (exec_array && ft_arraylen(exec_array) == 1)
	{
		print_cmd(word, exec_array[0], line);
		return (0);
	}
	else
	{
		ft_putchar('\n');
		print_array(exec_array);
		return (1);
	}
}

void	find_cmd(char **line, t_lst *env_lst)
{
	/*
	**	Warning if PATH is NULL;
	*/
	char	*word;

	if (ft_strrchr(*line, ' '))
		word = ft_strrchr(*line, ' ') + 1;
	else
	{
		word = ft_strdup(*line);
		if (browse_path(word, env_lst, line))
		{
			write_promptsh();
			ft_putstr(*line);
		}
	}
}