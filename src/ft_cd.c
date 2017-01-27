/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 08:53:00 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/24 17:36:26 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **array, char *env[])
{
	int	ret;

	ret = 0;
	if (array[1])
		ret = chdir(array[1]);
	else
		if (get_env_var("$HOME", env))
			ret = chdir(get_env_var("$HOME", env));
	if (ret == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(array[1]);
	}
}
