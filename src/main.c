/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:04:19 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/07 15:20:58 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_lst		*env_lst;
	char		*last_line;
	char		*line;
	extern char	**environ;

	last_line = NULL;
	env_lst = tab_to_list(environ);
	while (42)
	{
		line = NULL;
		signal(SIGINT, signal_handle);
		signal(SIGQUIT, signal_handle);
		write_promptsh();
		get_next_line(0, &line);
		if (line[0])
		{
			parssing_line(&line, env_lst, last_line);
			(last_line) ? free(last_line) : 0;
			last_line = ft_strdup(line);
			minishell(&env_lst, &last_line, line);
		}
		free(line);
	}
	del_lst(env_lst);
	return (1);
}
