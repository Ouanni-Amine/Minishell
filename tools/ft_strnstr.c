/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:34:55 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/20 13:50:08 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (haystack == NULL && needle != NULL && len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0] && i + ft_strlen((char *)needle) <= len)
		{
			if (!ft_strncmp(&haystack[i], needle, ft_strlen((char *)needle)))
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
