/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 09:54:27 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/02 19:51:11 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	cntrlC(int signal)
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	set_last_status(NULL, 1);
}
void	cntrlslash(int signal)
{
	ft_putstr_fd("Quit: 3\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	cntrlC_child(int signal)
{
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}
