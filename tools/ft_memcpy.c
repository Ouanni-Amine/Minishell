/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:52:24 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/18 16:52:37 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*p;
	unsigned char		*p1;

	i = 0;
	if (dst == src)
		return (dst);
	p = (const unsigned char *)src;
	p1 = (unsigned char *)dst;
	while (i < n)
	{
		p1[i] = p [i];
		i++;
	}
	return (dst);
}
