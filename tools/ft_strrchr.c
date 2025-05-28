/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:25:31 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/27 10:46:56 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	m;

	i = ft_strlen((char *)s);
	m = c;
	if (m == '\0')
		return ((char *)&s[i]);
	while (i > 0)
	{
		i--;
		if (s[i] == m)
			return ((char *)&s[i]);
	}
	return (NULL);
}
