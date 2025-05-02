/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:16:36 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/27 21:47:30 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

static int	check_atoll(const char *str, int *sign)
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

long long	ft_atoll(char *str, long long *num)
{
	int			sign;
	long long	res;
	int			i;
	long long	check;

	sign = 1;
	res = 0;
	check = 0;
	i = check_atoll(str, &sign);
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		check = res;
		res = res * 10 + (str[i] - '0');
		if (res < check && sign == 1)
			return (*num = LLONG_MAX, 0);
		if (res < check && sign != 1 && res != LLONG_MIN)
			return (*num = LLONG_MIN, 0);
		i++;
	}
	*num = res * sign;
	return (1);
}
