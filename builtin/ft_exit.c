/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:18:12 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/19 18:22:59 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

static int	check_atoi(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str, int *value)
{
	int			sign;
	long long	res;
	int			i;
	long long	check;

	sign = 1;
	res = 0;
	check = 0;
	i = check_atoi(str, &sign);
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		check = res;
		res = res * 10 + (str[i] - '0');
		if (res < check && sign == 1)
			return (-1);
		if (res < check && sign != 1 && res != LLONG_MIN)
			return (0);
		i++;
	}
	*value = (int)res * sign;
	return (1);
}

void	ft_exit(char **cmd, int last_cmd_status)
{
	int	fail;

	printf("exit\n");
	if (cmd[1])
	{
		if (!is_valide_num(cmd[1]) || ft_atoi(cmd[1], &fail) != 1)
		{
			error("minishell: exit: ", cmd[1],
				": numeric argument required", NULL);
			exit(255);
		}
		if (cmd[2])
		{
			error("minishell: exit: too many arguments", NULL, NULL, NULL);
			return ;
		}
		exit(fail % 256);
	}
	exit(last_cmd_status);
}
