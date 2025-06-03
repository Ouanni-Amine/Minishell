/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils13.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 06:48:47 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 07:00:13 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_code_norm1(char *local, t_shell *shell, t_norm *n)
{
	local = ft_itoa(shell->last_status);
	n->j = 0;
	n->len += ft_strlen(local);
	n->i += 2;
}

void	ft_code_norm2(char *local, t_shell *shell, t_norm *n, char *v)
{
	char	*str;

	str = get_env_value(shell->env, get_nameof_val(v, n->i));
	local = change_quotes(ft_strdup(str, '\0'));
	if (local)
		n->len += ft_strlen(local);
	n->i += ft_strlen(get_nameof_val(v, n->i)) + 1;
}

int	ft_code_norm3(t_norm *n, char *v)
{
	return (v[n->i] == '$' && v[n->i + 1]
		&& ((v[n->i + 1] >= '0' && v[n->i + 1] <= '9')));
}

char	*ft_code_norm4(t_token *tk, t_shell *shell)
{
	return (ft_get_the_true_str3
		(ft_strtrim(ft_add_val_in(tk->next->value, shell), " ")));
}
