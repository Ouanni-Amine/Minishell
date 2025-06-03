/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:02:23 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 05:04:02 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_lstsize(t_token *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	*get_nameof_val(char *val, size_t i)
{
	size_t	start;
	size_t	len;
	size_t	j;
	char	*dest;

	start = i + 1;
	len = 0;
	j = 0;
	while (val[start + len] && ft_symbols_max(val[start + len]))
		len++;
	dest = ft_malloc(len + 1);
	while (j < len)
	{
		dest[j] = val[start + j];
		j++;
	}
	dest[len] = '\0';
	return (dest);
}

size_t	ft_len_val(char *val, size_t i, t_env *env)
{
	char	*str;

	while (val[i])
	{
		if (val[i] == '$' && val[i + 1] && val[i + 1] != ' '
			&& val[i + 1] != '\t' && val[i + 1] != '\'' && val[i + 1] != '"')
		{
			str = get_env_value(env, get_nameof_val(val, i));
			return (ft_strlen(str));
		}
		i++;
	}
	return (0);
}

size_t	ft_fullstr_len(char *val, t_env *env)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (val[i])
	{
		if (val[i] == '$' && val[i + 1] && val[i + 1] != ' '
			&& val[i + 1] != '\t' && val[i + 1] != '\'' && val[i + 1] != '"')
		{
			count += ft_len_val(val, i, env);
			while (val[i] && val[i] != ' ' && val[i] != '\t')
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

size_t	ft_get_len(char *str)
{
	size_t	i;
	size_t	len;
	char	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			len++;
		i++;
	}
	return (len);
}
