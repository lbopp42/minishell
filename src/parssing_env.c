/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 13:11:57 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/07 13:58:09 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *origin, t_lst *env_lst)
{
	t_lst	*tmp;

	tmp = env_lst;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->name, origin))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	parssing_dollar(int i, t_lst *env_lst)
{
	char	*var_test;
	char	*new_line;
	int		tmp;

	tmp = i + 1;
	var_test = NULL;
	while (ft_isalnum(g_line[tmp]) || g_line[tmp] == '_')
		tmp++;
	if (!(var_test = ft_strsub(g_line, i + 1, tmp - i - 1)))
		return ;
	g_line[i] = '\0';
	new_line = ft_strdup(&((g_line)[0]));
	if (ft_isenv(env_lst, var_test))
		new_line = ft_stradd(new_line, get_env_var(var_test, env_lst));
	new_line = ft_stradd(new_line, &(g_line[tmp]));
	free(g_line);
	free(var_test);
	(g_line) = new_line;
}

void	pars_ptexcl(int i, char *last_line)
{
	char	*new_line;

	g_line[i] = '\0';
	new_line = ft_strdup(&(g_line[0]));
	if (last_line)
		new_line = ft_stradd(new_line, last_line);
	else
		new_line = ft_stradd(new_line, "exit");
	new_line = ft_stradd(new_line, &(g_line[i + 2]));
	free(g_line);
	g_line = new_line;
}

void	parssing_line(t_lst *env_lst, char *last_line)
{
	int i;

	i = 0;
	(void)last_line;
	while (g_line[i])
	{
		if (g_line[i] == '$' && g_line[i + 1] && ft_isalnum(g_line[i + 1]))
			parssing_dollar(i, env_lst);
		else if (g_line[i] == '!' && g_line[i + 1] && g_line[i + 1] == '!')
			pars_ptexcl(i, last_line);
		g_line[i] ? i++ : 0;
	}
}
