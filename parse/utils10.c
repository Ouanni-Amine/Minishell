/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:25:46 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 06:59:34 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_between_cotes(char *str, char type, t_norm *norm, char *dst)
{
	while (str[norm->i] && str[norm->i] != type)
	{
		dst[(norm->k)++] = str[norm->i];
		(norm->i)++;
	}
	if (str[norm->i] == type)
		(norm->i)++;
	return (dst);
}

int	ft_check_variable_max(char *str, size_t index)
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
		if (i == index + 1)
		{
			if (in_dquote)
				return (1);
			else if (in_squote)
				return (0);
		}
		i++;
	}
	return (1);
}

void	ft_set_norm1(t_norm *norm, t_token **current)
{
	norm->past = *current;
	*current = norm->next;
}

char	*ft_set_norm2(t_token *current)
{
	if (current->type == VARIABLE)
		current->value = ft_skip_thinks(current->value, 1);
	else
		current->value = ft_skip_thinks(current->value, 0);
	return (current->value);
}

t_token	*ft_set_norm3(t_norm *norm, t_token *current)
{
	norm->past = current;
	current = current->next;
	return (current);
}
