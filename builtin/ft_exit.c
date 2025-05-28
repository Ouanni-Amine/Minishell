/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:18:12 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/27 14:21:27 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	ft_exit(char **cmd, t_shell *shell)
{
	int	fail;

	if (!shell->is_pipe)
		ft_putstr_fd("exit\n", 2);
	if (cmd[1])
	{
		if (!is_valide_num(cmd[1]) || ft_atoi(cmd[1], &fail) != 1)
		{
			error("minishell: exit: ", cmd[1],
				": numeric argument required", NULL);
			my_exit(255);
		}
		if (cmd[2])
		{
			error("minishell: exit: too many arguments", NULL, NULL, NULL);
			return (1);
		}
		my_exit(fail % 256);
	}
	my_exit(shell->last_status);
	return (0);
}
