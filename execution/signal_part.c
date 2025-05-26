/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:12:34 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/25 17:27:20 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	signal_part(t_main *main)
{
	char	*cmd;

	cmd = main->cmd[0];
	if (ft_strnstr(cmd, "minishell", ft_strlen(cmd))
		|| ft_strnstr(cmd, "python", ft_strlen(cmd)))
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
