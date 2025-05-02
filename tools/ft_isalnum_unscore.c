/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum_unscore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:17:25 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/26 21:09:19 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	ft_isalnum_unscore(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90)
		|| (str[i] >= 97 && str[i] <= 122) || str[i] == 95)
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
