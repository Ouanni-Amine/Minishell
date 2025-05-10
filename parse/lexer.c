#include "minishell.h"

int	ft_true_nbr(char *str)
{
	int i = 0;
	int count = 0;
	int in_word = 0;

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

char *ft_skip_spaces(char *str)
{
	int i = 0, j = 0, cool = 0;
	int len = ft_true_nbr(str);
	char *new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return NULL;

	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		{
			if (cool == 0)
			{
				new_str[j++] = ' ';
				cool = 1;
			}
			i++;
		}
		while (str[i] && str[i] != ' ' && str[i] != '\t')
		{
			new_str[j++] = str[i++];
			cool = 0;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

int	ft_check_variable(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '$')
		return (1);
	if (!ft_strncmp("export", str, 6))
		return (1);
	return (0);
}

size_t ft_count_str(char *str)
{
	size_t count;
	int i;

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
	size_t len;
	char *new_str;
	int i;
	int j;

	len = ft_count_str(str);
	new_str = (char *) malloc(sizeof(char) * (len + 1));
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
	int i = 0;
	char *new_str;
	char **main_str;
	t_token *new_node;

	new_str = ft_make_space(str);
	main_str = ft_split(new_str, ' ');
	free(new_str);
	if (!main_str)
		return ;
	while (main_str[i])
	{
		new_node = malloc(sizeof(t_token));
		if (!new_node)
			break;
		new_node->value = strdup(main_str[i]);
		new_node->next = NULL;
		if (i == 0)
		{
			*head_lex = new_node;
		}
		else
		{
			current->next = new_node;
		}
		current = new_node;
		i++;
	}
	ft_free_1(i, main_str);
}

void	ft_set_type(t_token **head_lex)
{
	t_token *current = *head_lex;

	while (current)
	{
		char *val = current->value;

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

void	print_tokens(t_token *head)
{
	t_token *current = head;

	while (current)
	{
		printf("Value: [%s], Type: [%u]\n", current->value, current->type);
		current = current->next;
	}
}

void	free_tokens(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	lexer(char *str, t_token **head_lex)
{
	char *new_str = ft_skip_spaces(str);
	if (!new_str)
		return ;
	ft_add_val(new_str, head_lex);
	ft_set_type(head_lex);
	// print_tokens(*head_lex);
	// free_tokens(*head_lex);
	free(new_str);
}

