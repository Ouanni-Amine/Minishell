/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:12:34 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/09 20:23:42 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	signal_part(t_main *main)
{
	if (strnstr(main->cmd[0], "./", 2) && !strcmp(main->cmd[0] + 2, "a.out"))//note: this must be minishell!!
	{
		signal(SIGINT, cntrlc_specifique);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (!strnstr(main->cmd[0], "./", 2) && !strcmp(main->cmd[0], "a.out"))
	{
		signal(SIGINT, cntrlc_specifique);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, cntrlc_child);
		signal(SIGQUIT, cntrlslash);
	}
}
