/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:44:31 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 04:59:53 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_get_true_len(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_make_org_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 10)
			str[i] = '"';
		else if (str[i] == 11)
			str[i] = '\'';
		i++;
	}
	return (str);
}

void	ft_make_org_var(t_token **head_lex)
{
	size_t	i;
	t_token	*current;

	current = *head_lex;
	while (current)
	{
		i = 0;
		while (current->value[i])
		{
			if (current->value[i] == 10)
				current->value[i] = '"';
			else if (current->value[i] == 11)
				current->value[i] = '\'';
			i++;
		}
		current = current->next;
	}
}

char	*change_quotes(char *str)
{
	size_t	i;

	if (!str || !str[0])
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			str[i] = 10;
		else if (str[i] == '\'')
			str[i] = 11;
		i++;
	}
	return (str);
}

int	ft_find_export_word(t_token *current)
{
	while (current)
	{
		if (current->type == PIPE)
			return (0);
		else if (!ft_strcmp(current->value, "export") && current->type == WORD)
			return (1);
		current = current->next;
	}
	return (0);
}
