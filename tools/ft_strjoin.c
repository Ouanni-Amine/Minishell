/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:03:30 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/26 21:18:01 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

static char	*fill(const char *s, char *p)
{
	while (*s != '\0')
	{
		*p = *s;
		p++;
		s++;
	}
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*p;
	char	*r;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2, '\0'));
	if (!s2)
		return (ft_strdup(s1, '\0'));
	s1len = env_strlen(s1, '\0');
	s2len = env_strlen(s2, '\0');
	p = (char *)ft_malloc(sizeof(char) * (s1len + s2len +1));
	r = p;
	p = fill(s1, p);
	p = fill(s2, p);
	*p = '\0';
	return (r);
}
