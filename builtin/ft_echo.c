/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:32:13 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/18 17:31:30 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	echo_print(char **cmd, int i, int new_line)
{
	char	*res;

	res = NULL;
	while (cmd[i])
	{
		res = ft_strjoin(res, cmd[i]);
		if (cmd[i + 1])
			res = ft_strjoin(res, " ");
		i++;
	}
	if (new_line)
		res = ft_strjoin(res, "\n");
	ft_putstr_fd(res, 1);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	j;
	int	new_line;

	i = 1;
	new_line = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1])
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
		{
			new_line = 0;
			i++;
		}
		else
			break ;
	}
	echo_print(cmd, i, new_line);
	return (0);
}
