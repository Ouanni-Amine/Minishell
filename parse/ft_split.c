#include "minishell.h"

size_t    ft_get_true_len(const char *str, char c)
{
    size_t    i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (i);
}

void ft_make_org_var(t_token **head_lex)
{
	size_t i;
	t_token *current;

	current = *head_lex;
	while (current)
	{
		i = 0;
		while (current->value[i])
		{
			if (current->value[i] == 10)
				current->value[i] = '"';
			else if (current->value[i] == 11)
				current->value[i] = '\'';
			i++;
		}
		current = current->next;
	}
}

char *change_quotes(char *str)
{
	size_t i;

	if (!str || !str[0])
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			str[i] = 10;
		else if (str[i] == '\'')
			str[i] = 11;
		i++;
	}
	return (str);
}

int	ft_find_export_word(t_token *current)
{
	while (current)
	{
		if (current->type == PIPE)
			return (0);
		else if (!ft_strcmp(current->value, "export") && current->type == WORD)
			return (1);
		current = current->next;
	}
	return (0);
}

int ft_strstr_match(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!needle[0])
		return (1);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] && haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int count_words2(const char *s, char sep)
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
			break;
		count++;
		while (s[i])
		{
			if (is_quote(s[i]))
			{
				if (!in_quote)
				{
					in_quote = 1;
					quote_type = s[i];
				}
				else if (s[i] == quote_type)
					in_quote = 0;
			}
			else if (s[i] == sep && !in_quote)
				break;
			i++;
		}
	}
	return (count);
}

static char *word_dup(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = ft_malloc(end - start + 1);
	i = 0;
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char sep)
{
	char **result;
	int i = 0;
	int j;
	int start;
	int in_quote;
	char quote_type;
	int nbr_words;

	i = 0;
	j = 0;
	in_quote = 0;
	quote_type = 0;
	nbr_words = count_words2(s, sep);
	result = ft_malloc(sizeof(char *) * (nbr_words + 1));
	if (!result)
		return (NULL);
	while (s[i] && j < nbr_words)
	{
		while (s[i] == sep && !in_quote)
			i++;
		start = i;
		while (s[i])
		{
			if (is_quote(s[i]))
			{
				if (!in_quote)
				{
					in_quote = 1;
					quote_type = s[i];
				}
				else if (s[i] == quote_type)
					in_quote = 0;
			}
			else if (s[i] == sep && !in_quote)
				break;
			i++;
		}
		result[j++] = word_dup(s, start, i);
	}
	result[j] = NULL;
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_main	*ft_lstnew()
{
	t_main	*p;

	p = (t_main *)ft_malloc(sizeof(t_main));
	if (!p)
		return (NULL);
	p->cmd = NULL;
	p->redir = NULL;
	p->is_builtin = 0;
	p->next = NULL;
	return (p);
}

void ft_lstadd_back(t_main **lst, t_main *new)
{
	t_main *p;

	p = NULL;
	if (!new || !lst)
		return;
	if (!(*lst))
	{
		(*lst) = new;
	}
	else
	{
		p = *lst;
		while (p != NULL)
		{
			if (p->next == NULL)
			{
				p->next = new;
				return;
			}
			else
				p = p->next;
		}
	}
}

char *parse_strdup(const char *s1)
{
	int i;
	char *p;

	p = (char *) ft_malloc((ft_strlen((char *)s1) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

// static int myfunction1(char const *s1, char const *s2, int i)
// {
// 	int	b;

// 	b = 0;
// 	while (s1[i])
// 	{
// 		if (s1[i] == s2[b])
// 		{
// 			i++;
// 			b = 0;
// 		}
// 		else
// 		{
// 			if (!s2[b])
// 				return (i);
// 			b++;
// 		}
// 	}
// 	return (0);
// }

// static int myfunction2(char const *s1, char const *s2, int i)
// {
// 	int b;

// 	b = 0;
// 	while (i >= 0)
// 	{
// 		if (s1[i] == s2[b])
// 		{
// 			i--;
// 			b = 0;
// 		}
// 		else
// 		{
// 			if (!s2[b])
// 				return (i);
// 			b++;
// 		}
// 	}
// 	return (0);
// }

// static char *f(char *p)
// {
// 	p = (char *)ft_malloc(sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	p[0] = '\0';
// 	return (p);
// }

// char *ft_strtrim(char const *s1, char const *s2)
// {
// 	char *p;
// 	int i;
// 	int j;
// 	int b;

// 	b = 0;
// 	p = NULL;
// 	if (s1 && !s2)
// 		return (ft_strdup(s1, 0));
// 	if (!s1 || !s1[0])
// 		return ((char *)f(p));
// 	else
// 	{
// 		i = myfunction1(s1, s2, 0);
// 		j = myfunction2(s1, s2, ft_strlen((char *)s1) - 1);
// 		p = (char *)ft_malloc((j - i + 2) * sizeof(char));
// 		if (!p)
// 			return (NULL);
// 		if (j > 0)
// 			while (i <= j)
// 				p[b++] = s1[i++];
// 	}
// 	p[b] = '\0';
// 	return (p);
// }


char	*ft_strdup_updated(const char *s1, char c)
{
	size_t	i;
	char	*p;
	size_t	len;

	len = ft_get_true_len(s1, c);
	i = 0;
	p = (char *)ft_malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
