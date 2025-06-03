/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_protect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:29:38 by aouanni           #+#    #+#             */
/*   Updated: 2025/06/03 10:31:31 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	parse_protection(int signal)
{
	if (signal == SIGINT)
	{
		ft_putendl_fd("", 1);
		g_signal = SIGINT;
	}
}
