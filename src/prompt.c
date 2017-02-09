/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:59:44 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/07 15:21:37 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_prompt(void)
{
	char		*tab[10];
	int			random;
	int			i;
	static int	recur = 0;

	tab[0] = "Give me a command master > ";
	tab[1] = "What can I do for you > ";
	tab[2] = "I love eating commands > ";
	tab[3] = "Give me food > ";
	tab[4] = "Hit my keyboard ! > ";
	tab[5] = "I love you ! > ";
	tab[6] = "An other command pleeeaaase > ";
	tab[7] = "Yes my Lord ! > ";
	tab[8] = "RM -Rf all please ! > ";
	tab[9] = "Segmentation fault   (TROLL) > ";
	if (recur++ == 0)
		return ("Happy to see you again > ");
	i = 0;
	random = rand() % 10;
	while (i < random)
		i++;
	return (tab[i]);
}

void	write_promptsh(void)
{
	char			buf[256];
	char			*tmp;
	struct winsize	w;
	int				i;

	ioctl(0, TIOCGWINSZ, &w);
	i = 0;
	write(1, "\n", 1);
	while (i < w.ws_col)
	{
		write(1, "-", 1);
		i++;
	}
	ft_putendstr("\033[36m", getpwuid(getuid())->pw_name);
	ft_putstr("@\033[0;32m");
	ft_bzero(buf, 256);
	gethostname(buf, 256);
	tmp = ft_strcdup(buf, '.');
	ft_putendsp(tmp);
	free(tmp);
	ft_bzero(buf, 256);
	getcwd(buf, 256);
	ft_putendstr("\033[1;33m", buf);
	ft_putendstr("\n\033[31m", print_prompt());
	ft_putstr("\033[0m");
}
