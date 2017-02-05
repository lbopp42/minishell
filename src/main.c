/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:04:19 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/05 17:02:08 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_lst *env_lst;

	(void)ac;
	(void)av;
	env_lst = tab_to_list(env);
	minishell(env_lst);
	//del_lst(env_lst);
	return (1);
}
