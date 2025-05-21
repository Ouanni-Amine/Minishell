/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:54:27 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/20 18:26:37 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	cntrlc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	set_last_status(NULL, 1);
}

void	cntrlslash(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit: 3\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	cntrlc_child(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	heredoc_cntrlc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	exit(1);
}

void	cntrlc_specifique(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	set_last_status(NULL, 1);
}
