/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:15:30 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 07:03:39 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing_norm_max(t_norm *norm, t_main **head)
{
	norm->current_main = ft_lstnew();
	ft_lstadd_back(head, norm->current_main);
	norm->file_head = NULL;
	norm->cmd_index = 0;
	norm->cmd_count = ft_count_word_token(norm->current_token);
	norm->current_main->cmd = ft_malloc(sizeof(char *) * (norm->cmd_count + 1));
}

t_token	*ft_parsing_norm(t_norm *norm, t_main **head, t_shell *shell)
{
	if (!norm->current_main)
		ft_parsing_norm_max(norm, head);
	if (norm->current_token->type >= 2 && norm->current_token->type <= 5)
	{
		ft_append_in_file_struct(&norm->current_token,
			&norm->file_head, shell);
		norm->current_main->redir = norm->file_head;
	}
	else if (norm->current_token->type == 0 || norm->current_token->type == 6
		|| norm->current_token->type == 7 || norm->current_token->type == 8)
		ft_append_in_main_struct(norm->current_main,
			&norm->current_token, &norm->cmd_index);
	else if (norm->current_token->type == PIPE)
	{
		norm->current_main->cmd[norm->cmd_index] = NULL;
		norm->current_main = NULL;
		norm->current_token = norm->current_token->next;
	}
	else
		norm->current_token = norm->current_token->next;
	return (norm->current_token);
}

void	ft_parsing(t_token **head_lex, t_main **head, t_shell *shell)
{
	t_norm	norm;

	norm.current_token = *head_lex;
	norm.current_main = NULL;
	norm.file_head = NULL;
	norm.cmd_index = 0;
	while (norm.current_token)
	{
		norm.current_token = ft_parsing_norm(&norm, head, shell);
	}
	if (norm.current_main)
		norm.current_main->cmd[norm.cmd_index] = NULL;
	norm.current_main = *head;
	while (norm.current_main)
	{
		if (norm.current_main->cmd[0]
			&& ft_check_if_is_built(norm.current_main->cmd[0]))
			norm.current_main->is_builtin = 1;
		norm.current_main = norm.current_main->next;
	}
}
