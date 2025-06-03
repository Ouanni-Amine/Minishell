/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils12.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 06:48:02 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 06:48:29 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_make_spaces_norm2(char *new_str, size_t *i, size_t *j)
{
	new_str[(*j)++] = ' ';
	new_str[(*j)++] = '<';
	new_str[(*j)++] = '<';
	new_str[(*j)++] = ' ';
	(*i) += 2;
}

void	ft_make_spaces_norm3(char *new_str, size_t *i, size_t *j)
{
	new_str[(*j)++] = ' ';
	new_str[(*j)++] = '>';
	new_str[(*j)++] = ' ';
	(*i)++;
}

char	ft_make_with_space_1(char *new_str, char *str,
	char in_quote, t_norm *norm)
{
	in_quote = str[norm->i];
	new_str[norm->j++] = str[norm->i++];
	return (in_quote);
}

char	ft_make_with_space_2(char *new_str, char *str,
	char in_quote, t_norm *norm)
{
	in_quote = 0;
	new_str[norm->j++] = str[norm->i++];
	return (in_quote);
}

int	ft_strstr_match(const char *main_str, const char *str)
{
	size_t	i;
	size_t	j;

	if (!str[0])
		return (1);
	i = 0;
	while (main_str[i])
	{
		j = 0;
		while (main_str[i + j] && main_str[i + j] == str[j])
		{
			if (str[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
