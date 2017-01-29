/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 13:11:57 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/29 15:16:28 by lbopp            ###   ########.fr       */
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

char	**parssing_var(char *tab[], char *env[])
{
	int		wd;
	int		let;
	int		size;
	int		tmp;
	char	*var_test;
	char	*string;

	(void)env;
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
				while (tab[wd][let + tmp] && ft_isalpha(tab[wd][let + tmp]))
				{
					size++;
					tmp++;
				}
				printf("size = %d\n", size);
				if (!(var_test = (char*)malloc(sizeof(char) * size + 1)))
					return (NULL);
				var_test = ft_strncpy(var_test, &(tab[wd][let]), size);
				var_test[size] = '\0';
				printf("[var = %s]\n", var_test);
				printf("taille avant = %d\n", let - 1);
				printf("apres = %c\n", tab[wd][let + tmp]);
				printf("La taille d'apres = %zu\n", ft_strlen(&tab[wd][let + tmp]));
				if (ft_isenv(env, var_test))
				{
					//size = let - 1 + ft_strlen(&tab[wd][let + tmp]) +
					//	ft_strlen(get_env_var(var_test + 1, env));
					tab[wd][let - 1] = '\0';
					//if (!(string = (char*)malloc(sizeof(char) * size)))
					//	return (NULL);
					string = ft_strdup(&tab[wd][0]);
					printf("string1= [%s]\n", string);
					string = ft_stradd(string, get_env_var(var_test, env));
					printf("string2= [%s]\n", string);
					string = ft_stradd(string, &tab[wd][let + tmp]);
					printf("string final= [%s]\n", string);
				}
			}
			let++;
		}
		wd++;
	}
	return (tab);
}
