/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:57:27 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/19 14:29:06 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	error(char *str1, char *str2, char *str3, char *str4)
{
	char	*res;

	if (!str2 && str1)
	{
		res = ft_strjoin(str1, "\n");
		write(2, res, ft_strlen(res, '\0'));
		return ;
	}
	if (str2)
		res = ft_strjoin(str1, str2);
	if (str3)
		res = ft_strjoin(res, str3);
	if (str4)
		res = ft_strjoin(res, str4);
	res = ft_strjoin(res, "\n");
	write(2, res, ft_strlen(res, '\0'));
}
