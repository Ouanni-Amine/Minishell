/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:58:55 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 05:02:37 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_variable(char *str)
{
	size_t	i;
	int		in_dquote;
	int		in_squote;

	i = 0;
	in_dquote = 0;
	in_squote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		if (str[i] == '$' && str[i + 1]
			&& str[i + 1] != ' ' && str[i + 1] != '\t'
			&& ft_symbols(str[i + 1]))
		{
			if (!in_squote || in_dquote)
				return (1);
		}
		i++;
	}
	return (0);
}

size_t	ft_count_str(char *str)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		i++;
		count++;
	}
	i--;
	while (i >= 0)
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			i--;
			count--;
		}
		else
			return (count);
	}
	return (count);
}

int	ft_symbols_max(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	if (c == '?' || c == '$')
		return (0);
	return (0);
}

int	ft_symbols(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_' || c == '?' )
		return (1);
	return (0);
}

int	ft_isspaces_inside(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
