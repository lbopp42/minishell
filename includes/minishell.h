/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:11:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/10 14:55:56 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

typedef struct	s_info
{
	struct termios	init_term;
}				t_info;

void	add_lst(t_lst **lst, char *array);
void	change_oldpwd(t_lst **env, char *buf);
void	change_pwd(t_lst **env);
void	create_lst(t_lst **lst, char *array);
void	default_term(void);
void	del_array(char *array[]);
void	del_lst(t_lst *lst);
int		error_arg_env(void);
void	exec_command(char *array[], t_lst *env);
void	ft_cd(char **array, t_lst **env);
void	ft_echo(char **array);
void	ft_env(t_lst *env);
void	ft_exit(void);
void	ft_unsetenv(t_lst *env, char *name);
char	*get_env_var(char *origin, t_lst *env);
char	*get_path(t_lst *env, char *command);
void	init_sigleton(void);
void	init_term(void);
char	**list_to_tab(t_lst *lst);
void	manage_signal(void);
void	minishell(t_lst **env_lst, char **last_line, char *line);
void	parssing_line(char **line, t_lst *env_lst, char *last_line);
void	print_signal(int signum);
void	ft_setenv(t_lst **env, char *var, char *valeur);
void	signal_handle(int signal);
t_info	*singleton(t_info *data);
t_lst	*tab_to_list(char *array[]);
char	**transf_var(int *let, t_lst **env, int *wd, char *array[]);
char	**transf_var2(char *array[], int *wd, char *var_test, char *string);
int		treatment_builtins(char *array[], t_lst **env);
char	*verif_access(t_lst *env, char *command);
void	write_promptsh(void);

#endif
