/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:49:52 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/28 19:44:08 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

char	*ft_strdup(const char *s1, char c)
{
	size_t	i;
	char	*p;
	size_t	len;

	len = env_strlen(s1, c);
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
