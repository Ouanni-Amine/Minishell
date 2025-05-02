/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_strdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:46:01 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/26 21:14:01 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

char	*env_strdup(const char *s1, char c)
{
	size_t	i;
	char	*p;
	size_t	len;

	len = env_strlen(s1, c);
	i = 0;
	p = (char *)malloc((len + 1) * sizeof(char));
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
