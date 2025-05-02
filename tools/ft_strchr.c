/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:01:30 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/26 21:17:32 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	m;

	i = 0;
	m = c;
	if (m == '\0')
		return ((char *)&s[env_strlen(s, '\0')]);
	while (s[i] != '\0')
	{
		if (s[i] == m)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
