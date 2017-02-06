/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:59:44 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/06 17:30:01 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_prompt()
{
	char	*tab[] = {"Give me a command master > ", "What can I do for you > ",
	"I love eating commands > ", "Give me food > ", "Hit my keyboard ! > ",
	"I love you ! > ", "An other command pleeeaaase > ", "Yes my Lord ! > ",
	"RM -Rf all please ! > ", "Segmentation fault   (TROLL) > "};
	int		random;
	int		i;

	i = 0;
	random = rand() % 10;
	while (i < random)
		i++;
	return(tab[i]);
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
	ft_bzero(buf, 256);
	ft_putstr("\033[36m");
	getlogin_r(buf, 256);
	ft_putendch(buf, '@');
	ft_putstr("\033[0;32m");
	ft_bzero(buf, 256);
	gethostname(buf, 256);
	tmp = ft_strcdup(buf, '.');
	ft_putendsp(tmp);
	free(tmp);
	ft_bzero(buf, 256);
	getcwd(buf, 256);
	ft_putstr("\033[1;33m");
	ft_putendl(buf);
	ft_putstr("\033[31m");
	ft_putstr(print_prompt());
	ft_putstr("\033[0m");
}