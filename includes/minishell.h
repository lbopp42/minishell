/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:11:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/27 14:14:38 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>

typedef struct	s_lst
{
	char			*name;
	char			*content;
	struct s_lst	*next;
}				t_lst;

void	add_lst(t_lst **lst, char *array);
void	create_lst(t_lst **lst, char *array);
void	exec_command(char *array[], int ac, char *av[], char *env[]);
void	ft_cd(char **array, char *env[]);
void	ft_echo(char **array);
void	ft_env(char *env[]);
void	ft_unsetenv(t_lst *env, char *name);
char	*get_env_var(char *origin, char *env[]);
char	*get_path(char *env[], char *command);
char	**list_to_tab(t_lst *lst);
void	minishell(int ac, char *av[], char *env[]);
t_lst	*ft_setenv(t_lst *env, char *var, char *valeur);
t_lst	*tab_to_list(char *array[]);
int		treatment_builtins(char *array[], char **env[]);

#endif
