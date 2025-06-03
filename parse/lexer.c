/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:01:57 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 01:40:02 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_export_type(t_token **head_lex)
{
	t_token	*current;
	char	*val;

	current = *head_lex;
	while (current)
	{
		val = current->value;
		if (ft_strstr_match(current->value, "export")
			&& current->next && current->next->type == VARIABLE)
		{
			val = ft_get_the_true_str3(current->value);
			if (!strcmp(val, "export") && ft_strcmp(val, current->value))
				current->type = JUST_EXPORT;
		}
		current = current->next;
	}
}

void	ft_set_type(t_token **head_lex)
{
	t_token	*current;
	char	*val;

	current = *head_lex;
	while (current)
	{
		val = current->value;
		if (!ft_strncmp("|", val, 1) && ft_strlen(val) == 1)
			current->type = PIPE;
		else if (!ft_strncmp("<", val, 1) && ft_strlen(val) == 1)
			current->type = REDIR_IN;
		else if (!ft_strncmp(">", val, 1) && ft_strlen(val) == 1)
			current->type = REDIR_OUT;
		else if (!ft_strncmp(">>", val, 2) && ft_strlen(val) == 2)
			current->type = REDIR_APPEND;
		else if (!ft_strncmp("<<", val, 2) && ft_strlen(val) == 2)
			current->type = HEREDOC;
		else if (ft_check_variable(val))
			current->type = VARIABLE;
		else
			current->type = WORD;
		current = current->next;
	}
}

void	ft_add_val(char *str, t_token **head_lex)
{
	t_token	*current;
	int		i;
	char	*new_str;
	char	**main_str;
	t_token	*new_node;

	i = 0;
	new_str = ft_make_space(str);
	main_str = ft_split(new_str, ' ');
	if (!main_str)
		return ;
	while (main_str[i])
	{
		new_node = ft_malloc(sizeof(t_token));
		if (!new_node)
			break ;
		new_node->value = ft_strdup(main_str[i], '\0');
		new_node->next = NULL;
		if (i == 0)
			*head_lex = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
}

void	lexer(char *str, t_token **head_lex)
{
	ft_add_val(str, head_lex);
	ft_set_type(head_lex);
	ft_set_export_type(head_lex);
}
