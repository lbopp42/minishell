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

static void	launch_minishell(t_lst **env_lst, char **last_line)
{
	g_line = NULL;
	singleton_prompt(1);
	manage_signal();
	write_promptsh();
	get_line(*env_lst);
	singleton_prompt(2);
	if (g_line && g_line[0])
	{
		parssing_line(*env_lst, *last_line);
		(*last_line) ? free(*last_line) : 0;
		*last_line = ft_strdup(g_line);
		minishell(env_lst, last_line);
	}
	free(g_line);
}

int			main(void)
{
	t_lst		*env_lst;
	char		*last_line;
	extern char	**environ;

	last_line = NULL;
	init_term();
	env_lst = tab_to_list(environ);
	while (42)
		launch_minishell(&env_lst, &last_line);
	return (1);
}
