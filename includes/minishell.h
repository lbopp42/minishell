/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:11:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/29 11:07:55 by lbopp            ###   ########.fr       */
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
void	change_oldpwd(t_lst *env, char *buf);
void	change_pwd(t_lst *env);
void	create_lst(t_lst **lst, char *array);
void	del_lst(t_lst *lst);
int		error_arg_env(void);
void	exec_command(char *array[], int ac, char *av[], char *env[]);
void	ft_cd(char **array, char **env[]);
void	ft_echo(char **array);
void	ft_env(char *env[]);
void	ft_unsetenv(t_lst *env, char *name);
char	*get_env_var(char *origin, char *env[]);
char	*get_path(char *env[], char *command);
char	**list_to_tab(t_lst *lst);
void	minishell(int ac, char *av[], char *env[]);
char	**parssing_var(char *tab[], char *env[]);
void	print_signal(int signum);
t_lst	*ft_setenv(t_lst *env, char *var, char *valeur);
t_lst	*tab_to_list(char *array[]);
int		treatment_builtins(char *array[], char **env[]);

#endif
