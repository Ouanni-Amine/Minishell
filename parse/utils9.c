/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:12:55 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/17 14:42:45 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_if_is_built(char *value)
{
	if (!value)
		return (0);
	if (!ft_strcmp(value, "echo"))
		return (1);
	else if (!ft_strcmp(value, "cd"))
		return (1);
	else if (!ft_strcmp(value, "pwd"))
		return (1);
	else if (!ft_strcmp(value, "export"))
		return (1);
	else if (!ft_strcmp(value, "unset"))
		return (1);
	else if (!ft_strcmp(value, "env"))
		return (1);
	else if (!ft_strcmp(value, "exit"))
		return (1);
	return (0);
}

void	ft_exit_syntax_error(void)
{
	ft_putendl_fd("minishell: syntax error", 2);
	my_clean();
}

char	*ft_skip_thinks(char *str, int cool)
{
	if (cool)
		return (ft_get_the_true_str2(str));
	return (ft_get_the_true_str3(str));
}

int	next_qt(char *str, int i, char type)
{
	while (str[++i])
	{
		if (str[i] == type)
			return (1);
	}
	return (0);
}

size_t	ft_true_str3_len(char *str)
{
	t_norm	norm;
	char	quote;

	norm.i = 0;
	norm.len = 0;
	while (str[norm.i])
	{
		if (str[norm.i] == '"' || str[norm.i] == '\'')
		{
			quote = str[norm.i++];
			while (str[norm.i] && str[norm.i] != quote)
			{
				norm.len++;
				norm.i++;
			}
			if (str[norm.i] == quote)
				norm.i++;
		}
		else
		{
			norm.len++;
			norm.i++;
		}
	}
	return (norm.len);
}
