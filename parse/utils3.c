/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:52:26 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 05:00:45 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_main	*ft_lstnew(void)
{
	t_main	*p;

	p = (t_main *)ft_malloc(sizeof(t_main));
	if (!p)
		return (NULL);
	p->cmd = NULL;
	p->redir = NULL;
	p->is_builtin = 0;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_back(t_main **lst, t_main *new)
{
	t_main	*p;

	p = NULL;
	if (!new || !lst)
		return ;
	if (!(*lst))
		(*lst) = new;
	else
	{
		p = *lst;
		while (p != NULL)
		{
			if (p->next == NULL)
			{
				p->next = new;
				return ;
			}
			else
				p = p->next;
		}
	}
}

char	*ft_strdup_updated(const char *s1, char c)
{
	size_t	i;
	char	*p;
	size_t	len;

	len = ft_get_true_len(s1, c);
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
