/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 13:21:02 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/27 10:49:03 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **array)
{
	int	i;

	i = 1;
	while (array[i])
		ft_putendsp(array[i++]);
	write(1, "\n", 1);
}
