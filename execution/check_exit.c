/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:08:29 by aouanni           #+#    #+#             */
/*   Updated: 2025/06/02 11:16:11 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	check_exit(int status)
{
	int	stat;

	if (WIFEXITED(status))
		stat = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		stat = WTERMSIG(status) + 128;
		g_signal = WTERMSIG(status);
	}
	return (stat);
}
