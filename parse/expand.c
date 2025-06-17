/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:35:04 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 17:41:16 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_val_in(char *val, t_shell *shell)
{
	char	*full_str;
	t_norm	norm;
	char	*local;

	norm.i = 0;
	norm.k = 0;
	norm.len = 0;
	norm.j = 0;
	local = NULL;
	if (!val)
		return (NULL);
	ft_add_val_len_norm(val, shell, &norm, local);
	full_str = ft_malloc(norm.len + 1);
	norm.i = 0;
	norm.k = 0;
	ft_add_val_str_norm(val, &norm, shell, full_str);
	return (full_str);
}

t_token	*ft_add_token(t_token *current)
{
	char	**new_str;
	t_token	*org;
	t_token	*current_next;
	size_t	i;
	t_token	*new_token;

	i = 0;
	new_str = ft_split(current->value, ' ');
	if (!new_str[0])
		return (NULL);
	current_next = current->next;
	org = current;
	current->value = new_str[i++];
	current->type = EXPORT_VAL;
	while (new_str[i])
	{
		new_token = ft_build_token(new_str[i]);
		current->next = new_token;
		current = current->next;
		i++;
	}
	if (current_next)
		current->next = current_next;
	return (org);
}

t_token	*ft_check_val_norm_max(t_norm *norm, t_token *current, t_shell *shell)
{
	current->value = ft_add_val_in(current->value, shell);
	current = ft_add_token(current);
	norm->past = current;
	current = norm->next;
	return (current);
}

t_token	*ft_check_val_norm(t_norm *norm, t_token *ct,
							t_shell *shell, t_token **tk)
{
	if (norm->past != NULL && norm->past->type == 5 && ct->type == 6)
		ft_set_norm1(norm, &ct);
	else if (norm->past != NULL
		&& (norm->past->type >= 2 && norm->past->type <= 4) && ct->type == 6)
		ft_set_norm1(norm, &ct);
	else if (norm->past && norm->past->type == 8 && ct->type == 6)
		ct = ft_check_val_norm_max(norm, ct, shell);
	else if (!ft_strcmp((*tk)->value, "export")
		&& (*tk)->type == 6 && ft_if_key_valid(ct->value) && ct->type == 6)
		ct = ft_check_val_norm_max(norm, ct, shell);
	else if (!ft_strcmp((*tk)->value, "export") && ft_if_key_valid(ct->value))
	{
		ct->value = ft_add_val_in(ct->value, shell);
		ft_set_norm1(norm, &ct);
	}
	else if (ct->type == VARIABLE || ct->type == EXPORT_VAL)
	{
		ct->value = ft_add_val_in(ct->value, shell);
		if (ft_isspaces_inside(ct->value))
			ct = ft_add_token(ct);
		ft_set_norm1(norm, &ct);
	}
	else
		ft_set_norm1(norm, &ct);
	return (ct);
}

void	ft_check_val(t_token **token, t_shell *shell)
{
	t_token	*current;
	t_norm	norm;

	current = *token;
	norm.past = NULL;
	norm.token = token;
	while (current)
	{
		norm.next = current->next;
		current = ft_check_val_norm(&norm, current, shell, token);
	}
}
