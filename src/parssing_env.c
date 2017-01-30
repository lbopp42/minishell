/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 13:11:57 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/30 10:37:34 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	*get_env_var(char *origin, char *env[])
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], origin + 1))
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

void	transf_var()

char	**parssing_var(char *tab[], char *env[])
{
	int		wd;
	int		let;
	int		size;
	int		tmp;
	char	*var_test;
	char	*string;

	wd = 1;
	while (tab[wd])
	{
		size = 0;
		let = 0;
		while (tab[wd][let])
		{
			if (tab[wd][let] == '$')
			{
				let += 1;
				tmp = 0;
				while (tab[wd][let + tmp] && ft_isalnum(tab[wd][let + tmp]))
				{
					size++;
					tmp++;
				}
				if (!(var_test = (char*)malloc(sizeof(char) * size + 1)))
					return (NULL);
				var_test = ft_strncpy(var_test, &(tab[wd][let]), size);
				var_test[size] = '\0';
				tab[wd][let - 1] = '\0';
				string = ft_strdup(&tab[wd][0]);
				if (ft_isenv(env, var_test))
					string = ft_stradd(string, get_env_var(var_test, env));
				string = ft_stradd(string, &tab[wd][let + tmp]);
				free(tab[wd]);
				free(var_test);
				string[ft_strlen(string)] = '\0';
				tab[wd] = ft_strdup(string);
				free(string);
				let -= 2;
			}
			let++;
		}
		wd++;
	}
	return (tab);
}
