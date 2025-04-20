/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:49:52 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/18 16:50:16 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

char	*ft_strdup(const char *s1, char c)
{
	size_t	i;
	char	*p;
	size_t	len;

	len = ft_strlen(s1, c);
	i = 0;
	p = (char *)ft_malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
