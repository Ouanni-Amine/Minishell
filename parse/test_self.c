#include "minishell.h"

t_token *ft_check_str_norm(t_token *current, t_token **token, t_norm *norm)
{
	if (current->type == VARIABLE)
		current->value = ft_skip_thinks(current->value, 1);
	else
		current->value = ft_skip_thinks(current->value, 0);
	if ((!current->value) && ft_lstsize(*token) > 1)
	{
		norm->past = current;
		norm->tmp = current;
		if (norm->prev == NULL)
			(*token = current->next, current = *token);
		else
		{
			norm->prev->next = current->next;
			current = current->next;
		}
	}
	else
	{
		norm->past = current;
		norm->prev = current;
		current = current->next;
	}
	return (current);
}

void ft_check_str(t_token **token)
{
	t_token *current;
	t_norm	norm;

	current = *token;
	norm.prev = NULL;
	norm.past = NULL;
	while (current)
	{
		if (norm.past != NULL && norm.past->type == HEREDOC && current->value)
			(norm.past = current, current = current->next);
		else if (current->type == EXPORT_VAL)
		{
			current->value = ft_get_the_true_str2(current->value);
			norm.past = current;
			current = current->next;
		}
		else if (norm.past && (norm.past->type == REDIR_IN ||
					norm.past->type == REDIR_OUT))
			(norm.past = current, current = current->next);
		else
			current = ft_check_str_norm(current, token, &norm);
	}
}

void ft_check_str_variable(t_token **token)
{
	t_token *current = *token;
	t_token *prev = NULL;
	t_token *tmp;
	// char **check;

	while (current)
	{
		// check = ft_split(current->value, ' ');
		if (current->type == VARIABLE && (current->value[0] == '\0' || !ft_split(current->value, ' ')[0]) )
		{
			tmp = current;
			if (prev == NULL)
			{
				*token = current->next;
				current = *token;
			}
			else
			{
				prev->next = current->next;
				current = current->next;
			}
		}
		else
			(prev = current, current = current->next);
	}
}

char *ft_get_the_true_str(char *str)
{
	size_t i = 0;
	size_t len;
	char *new_str;
	size_t j = 0;

	if (!str)
		return (NULL);

	len = strlen(str);
	while (str[i] && (str[i] == '"' || str[i] == '\''))
		i++;
	while (len > i && (str[len - 1] == '"' || str[len - 1] == '\''))
		len--;

	new_str = ft_malloc(len - i + 1);
	if (!new_str)
		return NULL;

	while (i < len)
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}

int the_next_quote_is(char *str, int i, char type)
{
	while (str[++i])
	{
		if (str[i] == type)
			return (1);
	}
	return (0);
}

size_t ft_true_str3_len(char *str)
{
	size_t i = 0;
	size_t len = 0;

	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			char quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				len++;
				i++;
			}
			if (str[i] == quote)
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char *ft_between_cotes(char *str, char type, size_t *i, size_t *k, char *dst)
{
	while (str[*i] && str[*i] != type)
	{
		dst[(*k)++] = str[*i];
		(*i)++;
	}
	if (str[*i] == type)
		(*i)++;
	return (dst);
}

char *ft_get_the_true_str2(char *str)
{
	size_t i = 0;
	size_t k = 0;
	size_t final_len = ft_true_str3_len(str);
	char *new_str = ft_malloc(final_len + 1);
	char quote;

	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
			(new_str[k++] = str[i++], new_str[k++] = str[i++]);
		else if (str[i] == '$' && str[i + 1] && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		else if ((str[i] == '"' || str[i] == '\'') && the_next_quote_is(str, i, str[i]))
		{
			quote = str[i++];
			ft_between_cotes(str, quote, &i, &k, new_str);
		}
		else
			new_str[k++] = str[i++];
	}
	new_str[k] = '\0';
	return new_str;
}

char *ft_get_the_true_str3(char *str)
{
	size_t i = 0;
	size_t k = 0;
	size_t final_len = ft_true_str3_len(str);
	char *new_str = ft_malloc(final_len + 1);
	char quote;

	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
			(new_str[k++] = str[i++], new_str[k++] = str[i++]);
		else if (str[i] == '$' && str[i + 1] && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		else if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			ft_between_cotes(str, quote, &i, &k, new_str);
		}
		else
			new_str[k++] = str[i++];
	}
	new_str[k] = '\0';
	return (new_str);
}

char *ft_skip_thinks(char *str, int cool)
{
	if (cool)
		return (ft_get_the_true_str2(str));
	return (ft_get_the_true_str3(str));
}
