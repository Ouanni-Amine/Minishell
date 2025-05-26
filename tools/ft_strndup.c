/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:49:52 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/25 17:03:27 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

char	*ft_strndup(const char *s1, size_t len)
{
	size_t	i;
	char	*p;

	if (!s1)
		return (NULL);
	i = 0;
	p = (char *)ft_malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
