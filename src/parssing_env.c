/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 13:11:57 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/27 10:56:09 by lbopp            ###   ########.fr       */
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

void	parssing_var(char **tab[], char *env[])
{
	int		i;
	int		j;
	int		k;
	char	*var;

	i = 1;
	j = 0;
	while ((*tab)[i])
	{
		k = 0;
		printf("TEST\n");
		while ((*tab)[i][k])
		{
			if ((*tab)[i][k] == '$')
			{
				k++;
				while ((*tab)[i][k + j] && (*tab)[i][k + j] >= 65 &&
						(*tab)[i][k + j] <= 90)
				{
					j++;
				}
				var = ft_strcdup(&((*tab)[i][k]), (*tab)[i][k + j]);
				printf("var = %s\n", var);
			}
			k++;
			if (get_env_var(var, env))
			{
				
			}
		}
		i++;
	}
}
