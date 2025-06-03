/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 06:46:11 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 06:47:38 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_set_norm4(t_token **token, t_token **prev, t_token *current)
{
	if (*prev == NULL)
	{
		*token = current->next;
		current = *token;
	}
	else
	{
		(*prev)->next = current->next;
		current = current->next;
	}
	return (current);
}

int	fquote(char c)
{
	return (c == '"' || c == '\'');
}

void	ft_add_token_pipe(t_token **current)
{
	while (*current)
	{
		if ((*current)->type == PIPE && (*current)->next == NULL)
		{
			(*current)->next = ft_malloc(sizeof(t_token));
			(*current)->next->value = ft_strdup("|", '\0');
			(*current)->next->type = PIPE;
			(*current)->next->next = NULL;
			(*current) = (*current)->next;
			break ;
		}
		else
			(*current) = (*current)->next;
	}
}

void	ft_get_true_str_norm(char *new_str, t_norm *norm, char *str)
{
	new_str[norm->k++] = str[norm->i++];
	new_str[norm->k++] = str[norm->i++];
}

void	ft_make_spaces_norm1(char *new_str, size_t *i, size_t *j)
{
	new_str[(*j)++] = ' ';
	new_str[(*j)++] = '>';
	new_str[(*j)++] = '>';
	new_str[(*j)++] = ' ';
	(*i) += 2;
}
