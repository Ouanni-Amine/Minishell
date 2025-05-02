/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:49:15 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/27 15:54:31 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

static int	start(const char *s, const char*s1)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (s[i] != '\0')
	{
		while (s1[j] != '\0')
		{
			if (s[i] == s1[j])
			{
				i++;
				j = 0;
			}
			else
				j++;
		}
	}
	return (i);
}

static int	end(const char *s, const char*s1)
{
	int	y;
	int	k;

	y = 0;
	k = (env_strlen(s, '\0') - 1);
	while (s1[y] != '\0')
	{
		if (k < 0)
			return (k);
		if (s[k] == s1[y])
		{
			k--;
			y = 0;
		}
		else
			y++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		m;
	char	*p;
	int		o;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1, '\0'));
	i = start(s1, set);
	j = end(s1, set);
	m = 0;
	o = (j + 1) - i;
	if (i > j)
		return (ft_strdup("", '\0'));
	p = (char *)ft_malloc(sizeof(char) * (o + 1));
	while (m < o)
		p[m++] = s1[i++];
	p[m] = '\0';
	return (p);
}
