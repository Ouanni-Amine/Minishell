/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:58:15 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 15:32:56 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_count_word2_norm(const char *s, int *i,
	int *in_quote, char quote_type)
{
	while (s[*i])
	{
		if (s[*i] == '"' || s[*i] == '\'')
		{
			if (!*in_quote)
			{
				*in_quote = 1;
				quote_type = s[*i];
			}
			else if (s[*i] == quote_type)
				*in_quote = 0;
		}
		else if (s[*i] == ' ' && !*in_quote)
			break ;
		(*i)++;
	}
}

int	count_words2(const char *s, char sep)
{
	int		i;
	int		count;
	int		in_quote;
	char	quote_type;

	i = 0;
	count = 0;
	in_quote = 0;
	quote_type = 0;
	while (s[i])
	{
		while (s[i] == sep && !in_quote)
			i++;
		if (!s[i])
			break ;
		count++;
		ft_count_word2_norm(s, &i, &in_quote, quote_type);
	}
	return (count);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = ft_malloc(end - start + 1);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

void	split_norm(t_norm *norm, const char *s,
	int *in_quote, char quote_type)
{
	while (s[(*norm).i])
	{
		if (s[(*norm).i] == '"' || s[(*norm).i] == '\'')
		{
			if (!*in_quote)
			{
				*in_quote = 1;
				quote_type = s[(*norm).i];
			}
			else if (s[(*norm).i] == quote_type)
				*in_quote = 0;
		}
		else if (s[(*norm).i] == ' ' && !*in_quote)
			break ;
		(*norm).i++;
	}
}

char	**ft_split(char const *s, char sep)
{
	char	**result;
	t_norm	norm;
	int		in_quote;
	char	quote_type;
	size_t	nbr_words;

	norm.i = 0;
	norm.j = 0;
	norm.start = 0;
	in_quote = 0;
	quote_type = 0;
	nbr_words = count_words2(s, sep);
	result = ft_malloc(sizeof(char *) * (nbr_words + 1));
	while (s[norm.i] && norm.j < nbr_words)
	{
		while (s[norm.i] == sep && !in_quote)
			norm.i++;
		norm.start = norm.i;
		split_norm(&norm, s, &in_quote, quote_type);
		result[norm.j++] = word_dup(s, norm.start, norm.i);
	}
	result[norm.j] = NULL;
	return (result);
}
