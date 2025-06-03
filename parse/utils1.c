/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:28:09 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 04:56:47 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_str_with_space(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
		{
			count += 4;
			i += 2;
		}
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			count += 3;
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

void	ft_make_str_with_space_norm(char *str, char *new_str,
	size_t *i, size_t *j)
{
	if (str[(*i)] == '>' && str[(*i) + 1] == '>')
		ft_make_spaces_norm1(new_str, i, j);
	else if (str[(*i)] == '<' && str[(*i) + 1] == '<')
		ft_make_spaces_norm2(new_str, i, j);
	else if (str[(*i)] == '>')
		ft_make_spaces_norm3(new_str, i, j);
	else if (str[(*i)] == '<')
	{
		new_str[(*j)++] = ' ';
		new_str[(*j)++] = '<';
		new_str[(*j)++] = ' ';
		(*i)++;
	}
	else if (str[(*i)] == '|')
	{
		new_str[(*j)++] = ' ';
		new_str[(*j)++] = '|';
		new_str[(*j)++] = ' ';
		(*i)++;
	}
	else
		new_str[(*j)++] = str[(*i)++];
}

char	*ft_make_str_with_space(char *str)
{
	size_t	len;
	t_norm	norm;
	char	*new_str;
	char	in_quote;

	len = ft_count_str_with_space(str);
	norm.i = 0;
	norm.j = 0;
	new_str = (char *) ft_malloc(sizeof(char) * (len + 1));
	in_quote = 0;
	while (str[norm.i])
	{
		if (!in_quote && (str[norm.i] == '\'' || str[norm.i] == '"'))
			in_quote = ft_make_with_space_1(new_str, str, in_quote, &norm);
		else if (!in_quote)
			ft_make_str_with_space_norm(str, new_str, &norm.i, &norm.j);
		else if (in_quote && str[norm.i] == in_quote)
			in_quote = ft_make_with_space_2(new_str, str, in_quote, &norm);
		else if (in_quote)
			new_str[norm.j++] = str[norm.i++];
	}
	new_str[norm.j] = '\0';
	return (new_str);
}

char	*ft_make_str_with_org_space(char *str)
{
	size_t	len;
	size_t	i;
	char	*new_str;

	len = ft_strlen(str);
	i = 0;
	new_str = (char *) ft_malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		if (str[i] >= 9 && str[i] <= 13)
			new_str[i] = ' ';
		else
			new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_make_space(char *str)
{
	size_t	i;
	char	*old_str;
	char	*new_str;

	i = 0;
	old_str = ft_make_str_with_org_space(str);
	new_str = ft_make_str_with_space(old_str);
	return (new_str);
}
