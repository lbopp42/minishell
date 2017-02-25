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

void	parssing_dollar(char **line, int i, t_lst *env_lst)
{
	char	*var_test;
	char	*new_line;
	int		tmp;

	tmp = i + 1;
	var_test = NULL;
	while (ft_isalnum((*line)[tmp]) || (*line)[tmp] == '_')
		tmp++;
	if (!(var_test = ft_strsub((*line), i + 1, tmp - i - 1)))
		return ;
	(*line)[i] = '\0';
	new_line = ft_strdup(&((*line)[0]));
	if (ft_isenv(env_lst, var_test))
		new_line = ft_stradd(new_line, get_env_var(var_test, env_lst));
	new_line = ft_stradd(new_line, &((*line)[tmp]));
	free(*line);
	free(var_test);
	(*line) = new_line;
}

void	pars_ptexcl(char **line, int i, char *last_line)
{
	char	*new_line;

	(*line)[i] = '\0';
	new_line = ft_strdup(&((*line)[0]));
	if (last_line)
		new_line = ft_stradd(new_line, last_line);
	else
		new_line = ft_stradd(new_line, "exit");
	new_line = ft_stradd(new_line, &((*line)[i + 2]));
	free(*line);
	(*line) = new_line;
}

void	parssing_line(char **line, t_lst *env_lst, char *last_line)
{
	int i;

	i = 0;
	(void)last_line;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] && ft_isalnum((*line)[i + 1]))
			parssing_dollar(line, i, env_lst);
		else if ((*line)[i] == '!' && (*line)[i + 1] && (*line)[i + 1] == '!')
			pars_ptexcl(line, i, last_line);
		(*line)[i] ? i++ : 0;
	}
}
