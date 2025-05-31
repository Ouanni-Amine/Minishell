#include "minishell.h"

int	ft_true_nbr(char *str)
{
	int i;
	int count;
	int in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			count++;
			in_word = 1;
		}
		else if (in_word)
		{
			count++;
			in_word = 0;
		}
		i++;
	}
	return (count + 1);
}


int	ft_check_variable(char *str)
{
	size_t	i;
	int		in_dquote;
	int		in_squote;

	i = 0;
	in_dquote = 0;
	in_squote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		if (str[i] == '$' && str[i + 1] &&
			str[i + 1] != ' ' && str[i + 1] != '\t' && ft_symbols(str[i + 1]))
		{
			if (!in_squote || in_dquote)
				return (1);
		}
		i++;
	}
	return (0);
}

size_t	ft_count_str(char *str)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
		(i++, count++);
	i--;
	while (i >= 0)
	{
		if (str[i] == ' ' || str[i] == '\t')
			(i--, count--);
		else
			return (count);
	}
	return (count);
}

char *ft_make_it_clear(char *str)
{
	size_t	len;
	char	*new_str;
	int		i;
	int		j;

	len = ft_count_str(str);
	new_str = (char *) ft_malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (len > 0)
	{
		new_str[j++] = str[i++];
		len--;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	ft_add_val(char *str, t_token **head_lex)
{
	t_token *current;
	int i;
	char *new_str;
	char **main_str;
	t_token *new_node;

	i = 0;
	new_str = ft_make_space(str);
	main_str = ft_split(new_str, ' ');
	if (!main_str)
		return ;
	while (main_str[i])
	{
		new_node = ft_malloc(sizeof(t_token));
		if (!new_node)
			break;
		new_node->value = ft_strdup(main_str[i], '\0');
		new_node->next = NULL;
		if (i == 0)
			*head_lex = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
}

void	ft_set_type(t_token **head_lex)
{
	t_token *current;
	char *val;

	current = *head_lex;
	while (current)
	{
		val = current->value;

		if (!ft_strncmp("|", val, 1) && ft_strlen(val) == 1)
			current->type = PIPE;
		else if (!ft_strncmp("<", val, 1) && ft_strlen(val) == 1)
			current->type = REDIR_IN;
		else if (!ft_strncmp(">", val, 1) && ft_strlen(val) == 1)
			current->type = REDIR_OUT;
		else if (!ft_strncmp(">>", val, 2) && ft_strlen(val) == 2)
			current->type = REDIR_APPEND;
		else if (!ft_strncmp("<<", val, 2) && ft_strlen(val) == 2)
			current->type = HEREDOC;
		else if (ft_check_variable(val))
			current->type = VARIABLE;
		else
			current->type = WORD;

		current = current->next;
	}
}

void	ft_set_export_type(t_token **head_lex)
{
	t_token *current;
	char *val;

	current = *head_lex;
	while (current)
	{
		val = current->value;
		if (ft_strstr_match(current->value, "export") && current->next && current->next->type == VARIABLE)
		{
			val = ft_get_the_true_str3(current->value);
			if (!strcmp(val, "export") && ft_strcmp(val, current->value))
				current->type = JUST_EXPORT;
		}
		current = current->next;
	}
}

void	lexer(char *str, t_token **head_lex)
{
	ft_add_val(str, head_lex);
	ft_set_type(head_lex);
	ft_set_export_type(head_lex);
}
