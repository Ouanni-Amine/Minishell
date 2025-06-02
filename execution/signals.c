/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:54:27 by aouanni           #+#    #+#             */
/*   Updated: 2025/06/02 15:02:01 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	sig_handler(int signal)
{
	g_signal = signal;
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_cntrlc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	exit(1);
}

void	prepare_signals(void)
{
	g_signal = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	check_signal(int last_status)
{
	if (g_signal == SIGINT)
		ft_putendl_fd("", 1);
	else if (g_signal == SIGQUIT && last_status == 131)
		ft_putendl_fd("Quit: 3", 1);
}

void	change_handler(int code)
{
	if (code)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
