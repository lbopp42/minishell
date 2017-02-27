/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:42:05 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/30 17:25:06 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_signal(int signum)
{
	const int	array[] = {SIGABRT, SIGALRM, SIGBUS, SIGFPE, SIGHUP,
	SIGILL, SIGINT, SIGKILL, SIGPROF, SIGQUIT, SIGSEGV,
	SIGSTOP, SIGSYS, SIGTERM, SIGTRAP, SIGTSTP, SIGTTIN, SIGTTOU, SIGUSR1,
	SIGUSR2, SIGVTALRM, SIGXCPU, SIGXFSZ, 0};
	const char	*err_sign[] = {"Abort\n", "Alarm\n", "Bus error\n",
	"Floting point exception\n", "Hangup\n", "Illegal hardware instruction\n",
	"\n", "Killed\n", "Profile signal\n", "Quit\n", "Segmentation fault\n",
	"Suspended (signal)\n", "Invalid system call\n", "Terminated\n",
	"Trace trap\n", "Suspended", "Suspended (tty input)\n",
	"Suspended (tty output)\n", "User-defined signal 1\n",
	"User-defined signal 1\n", "Virtual time alarm\n", "cpu limit exceeded\n",
	"file size limit exceeded\n"};
	int			i;

	i = 0;
	while (array[i])
	{
		if (array[i] == signum)
			ft_putstr(err_sign[i]);
		i++;
	}
}

void	manage_signal(void)
{
	signal(SIGINT, signal_handle);
	signal(SIGQUIT, signal_handle);
}
