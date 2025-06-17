/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:45:15 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 17:40:38 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*create_file_node(t_token *tk, t_shell *shell)
{
	t_file	*new_file;

	new_file = ft_malloc(sizeof(t_file));
	new_file->token = tk->type;
	new_file->file = ft_strdup(ft_get_the_true_str3(tk->next->value), '\0');
	new_file->here_doc = -1;
	if (tk->type == 5 && tk->next->value && ft_check_expand(tk->next->value))
		new_file->expand = 1;
	else
		new_file->expand = 0;
	if ((tk->type >= 2 && tk->type <= 4) && tk->next->value
		&& ft_check_content(tk->next->value, tk->next->type, shell))
		new_file->ambiguous = 1;
	else
	{
		if (new_file->expand == 0 && tk->type != 5
			&& tk->next && tk->next->type == 6)
		{
			new_file->file = ft_code_norm4(tk, shell);
			new_file->file = ft_make_org_str(new_file->file);
		}
		new_file->ambiguous = 0;
	}
	new_file->next = NULL;
	return (new_file);
}

void	append_file(t_file **file_head, t_file *new_file)
{
	t_file	*temp;

	if (!*file_head)
	{
		*file_head = new_file;
		return ;
	}
	temp = *file_head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_file;
}

void	ft_append_in_file_struct(t_token **current_token, t_file **file_head,
	t_shell *shell)
{
	t_file	*new_file;

	if (!*current_token || !(*current_token)->next)
		return ;
	new_file = create_file_node(*current_token, shell);
	if (!new_file)
		return ;
	append_file(file_head, new_file);
	*current_token = (*current_token)->next->next;
}

size_t	ft_count_word_token(t_token *current)
{
	size_t	count;

	count = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == WORD || current->type == VARIABLE
			|| current->type == 7 || current->type == JUST_EXPORT)
			count++;
		else if (current->type >= REDIR_IN && current->type <= HEREDOC)
			current = current->next;
		current = current->next;
	}
	return (count);
}

void	ft_append_in_main_struct(t_main *current_main,
	t_token **current_token, size_t *cmd_index)
{
	if (!current_main || !current_main->cmd
		|| !current_token || !*current_token)
		return ;
	current_main->cmd[*cmd_index] = ft_strdup((*current_token)->value, '\0');
	(*cmd_index)++;
	*current_token = (*current_token)->next;
}
