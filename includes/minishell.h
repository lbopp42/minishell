/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:11:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/06 11:03:00 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>

void	add_lst(t_lst **lst, char *array);
void	change_oldpwd(t_lst *env, char *buf);
void	change_pwd(t_lst *env);
void	create_lst(t_lst **lst, char *array);
void	del_array(char *array[]);
void	del_lst(t_lst *lst);
int		error_arg_env(void);
void	exec_command(char *array[], t_lst *env);
void	ft_cd(char **array, t_lst *env);
void	ft_echo(char **array);
void	ft_env(t_lst *env);
void	ft_exit(void);
void	ft_unsetenv(t_lst *env, char *name);
char	*get_env_var(char *origin, t_lst *env);
char	*get_path(t_lst *env, char *command);
char	**list_to_tab(t_lst *lst);
void	minishell(t_lst *env_lst);
char	**parssing_var(char *tab[], t_lst *env_lst);
void	print_signal(int signum);
void	ft_setenv(t_lst *env, char *var, char *valeur);
t_lst	*tab_to_list(char *array[]);
char	**transf_var(int *let, t_lst *env, int *wd, char *tab[]);
char	**transf_var2(char *tab[], int *wd, char *var_test, char *string);
int		treatment_builtins(char *array[], t_lst *env);

#endif
