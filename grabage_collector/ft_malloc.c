/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:23:52 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/18 18:25:44 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	ft_free(void *ptr, int flag)
{
	static void	*lst[INT_MAX];
	static int	i;
	int			j;

	if (flag)
	{
		j = 0;
		while (lst[j])
			free(lst[j++]);
	}
	else
		lst[i++] = ptr;
}

void	my_exit(void)
{
	ft_free(NULL, 1);
	exit(1);
}

void	*ft_malloc(size_t n)
{
	void	*ptr;

	ptr = malloc(n);
	if (!ptr)
		my_exit();
	ft_free(ptr, 0);
	return (ptr);
}
