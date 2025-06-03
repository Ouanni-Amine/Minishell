/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:27:34 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/05/29 18:27:34 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_check_str_norm(t_token *current, t_token **token, t_norm *norm)
{
	current->value = ft_set_norm2(current);
	if ((!current->value) && ft_lstsize(*token) > 1)
	{
		norm->past = current;
		norm->tmp = current;
		if (norm->prev == NULL)
		{
			*token = current->next;
			current = *token;
		}
		else
		{
			norm->prev->next = current->next;
			current = current->next;
		}
	}
	else
	{
		norm->past = current;
		norm->prev = current;
		current = current->next;
	}
	return (current);
}

void	ft_check_str(t_token **token)
{
	t_token	*current;
	t_norm	norm;

	current = *token;
	norm.prev = NULL;
	norm.past = NULL;
	while (current)
	{
		if (norm.past != NULL && norm.past->type == HEREDOC && current->value)
			current = ft_set_norm3(&norm, current);
		else if (current->type == EXPORT_VAL)
		{
			current->value = ft_get_the_true_str2(current->value);
			norm.past = current;
			current = current->next;
		}
		else if (norm.past && (norm.past->type == REDIR_IN
				|| norm.past->type == REDIR_OUT))
			current = ft_set_norm3(&norm, current);
		else
			current = ft_check_str_norm(current, token, &norm);
	}
}

void	ft_check_str_variable(t_token **token)
{
	t_token	*current;
	t_token	*prev;
	t_token	*tmp;

	current = *token;
	prev = NULL;
	while (current)
	{
		if (current->type == 6 && (current->value[0] == '\0'
				|| !ft_split(current->value, ' ')[0]))
		{
			tmp = current;
			current = ft_set_norm4(token, &prev, current);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	current = *token;
	ft_add_token_pipe(&current);
}

char	*ft_get_the_true_str2(char *s)
{
	t_norm	n;
	char	*new_str;
	char	quote;

	n.i = 0;
	n.k = 0;
	new_str = ft_malloc(ft_true_str3_len(s) + 1);
	if (!new_str)
		return (NULL);
	while (s[n.i])
	{
		if (s[n.i] && s[n.i + 1] && s[n.i] == '$' && s[n.i + 1] == '$')
			ft_get_true_str_norm(new_str, &n, s);
		else if (s[n.i] == '$' && s[n.i + 1] && fquote(s[n.i + 1]))
			n.i++;
		else if ((s[n.i] == '"' || s[n.i] == '\'') && next_qt(s, n.i, s[n.i]))
		{
			quote = s[n.i++];
			ft_between_cotes(s, quote, &n, new_str);
		}
		else
			new_str[n.k++] = s[n.i++];
	}
	new_str[n.k] = '\0';
	return (new_str);
}

char	*ft_get_the_true_str3(char *str)
{
	t_norm	n;
	char	*new_str;
	char	quote;

	new_str = ft_malloc(ft_true_str3_len(str) + 1);
	n.i = 0;
	n.k = 0;
	if (!new_str)
		return (NULL);
	while (str[n.i])
	{
		if (str[n.i] && str[n.i + 1] && str[n.i] == '$' && str[n.i + 1] == '$')
			ft_get_true_str_norm(new_str, &n, str);
		else if (str[n.i] == '$' && str[n.i + 1] && fquote(str[n.i + 1]))
			n.i++;
		else if (str[n.i] == '"' || str[n.i] == '\'')
		{
			quote = str[n.i++];
			ft_between_cotes(str, quote, &n, new_str);
		}
		else
			new_str[n.k++] = str[n.i++];
	}
	new_str[n.k] = '\0';
	return (new_str);
}
