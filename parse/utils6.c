/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:24:16 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 16:41:01 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_val_len_norm(char *v, t_shell *shell, t_norm *n, char *local)
{
	while (v[(*n).i])
	{
		if (v[n->i] == '$' && v[n->i + 1]
			&& v[n->i + 1] == '?' && ft_check_variable_max(v, (*n).i))
		{
			ft_code_norm1(local, shell, n);
		}
		else if (ft_code_norm3(n, v))
		{
			local = "";
			n->i += 2;
		}
		else if (v[n->i] == '$' && v[n->i + 1]
			&& ft_symbols_max(v[n->i + 1]) && ft_check_variable_max(v, n->i))
			ft_code_norm2(local, shell, n, v);
		else
		{
			n->len++;
			n->i++;
		}
	}
}

void	ft_add_val_str_norm_special(t_norm *norm, t_shell *shell,
	char *full_str)
{
	char	*local;

	local = NULL;
	local = ft_itoa(shell->last_status);
	(*norm).j = 0;
	while (local[(*norm).j])
		full_str[((*norm).k)++] = local[((*norm).j)++];
	(*norm).i += 2;
}

void	ft_add_val_str_norm_simple(t_env *env, t_norm *norm,
	char *val, char *full_str)
{
	char	*local;
	char	*str;

	str = get_env_value(env, get_nameof_val(val, (*norm).i));
	local = change_quotes(ft_strdup(str, '\0'));
	if (local)
	{
		(*norm).j = 0;
		while (local[(*norm).j])
			full_str[((*norm).k)++] = local[((*norm).j)++];
	}
	(*norm).i += ft_strlen(get_nameof_val(val, (*norm).i)) + 1;
}

void	ft_add_val_str_norm(char *v, t_norm *n, t_shell *shell, char *full_str)
{
	char	*local;

	local = NULL;
	while (v[(*n).i])
	{
		if (v[(*n).i] == '$' && v[(*n).i + 1]
			&& v[(*n).i + 1] == '?' && ft_check_variable_max(v, (*n).i))
		{
			ft_add_val_str_norm_special(n, shell, full_str);
			continue ;
		}
		else if (v[(*n).i] == '$' && v[(*n).i + 1]
			&& ((v[(*n).i + 1] >= '0' && v[(*n).i + 1] <= '9')))
		{
			local = "";
			(*n).i += 2;
			continue ;
		}
		if (v[(*n).i] == '$' && v[(*n).i + 1] && ft_symbols_max(v[(*n).i + 1])
			&& ft_check_variable_max(v, (*n).i))
			ft_add_val_str_norm_simple(shell->env, n, v, full_str);
		else
			full_str[(*n).k++] = v[(*n).i++];
	}
	full_str[(*n).k] = '\0';
}

t_token	*ft_build_token(char *str)
{
	t_token	*new_token;

	new_token = ft_malloc(sizeof(t_token));
	new_token->next = NULL;
	new_token->type = EXPORT_VAL;
	new_token->value = ft_strdup(str, 0);
	return (new_token);
}
