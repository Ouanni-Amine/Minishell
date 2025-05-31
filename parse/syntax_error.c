#include "minishell.h"

int ft_check_place_of_special(t_token *current)
{
	if (!current->next)
		return (0);
	if ((current->type >= 2 && current->type <= 5) && current->next->type == 1)
		return (0);
	else if ((current->type >= PIPE && current->type <= HEREDOC) && ((current->next->type >= PIPE && current->next->type <= HEREDOC)))
		return (0);
	else if (current->type == current->next->type)
		return (0);
	return (1);

}

int ft_check_word_if_was_special(t_token *current)
{
	char *str;
	size_t i;
	int cool_double;
	int cool_single;

	i = 0;
	str = current->value;
	cool_double = 0;
	cool_single = 0;

	while (str[i])
	{
		if (str[i] == '\'')
			cool_single++;
		else if (str[i] == '"')
			cool_double++;
		i++;
	}
	if (cool_double % 2 != 0 || cool_single % 2 != 0)
		return (0);
	return (1);
}

int	ft_check_next_quote(char *str, char type, size_t *i)
{
	while (str[*i])
	{
		if (str[*i] == type)
			return (1);
		(*i)++;
	}
	return (0);
}

int ft_check_word_if_was_special2(t_token *current)
{
	char *str;
	size_t i;
	int cool_double;
	int cool_single;

	i = 0;
	if (!current || !current->value)
		return (0);
	str = current->value;
	cool_double = 0;
	cool_single = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (!ft_check_next_quote(str, str[i++], &i))
				return (0);
		}
		i++;
	}
	return (1);
}

void ft_exit_syntax_error()
{
	error("syntax error", 0, 0, 0);
	my_clean();
}

int ft_check_syntax_error(t_token *head_lex)
{
	t_token *current;
	t_token *past;
	int cool;

	current = head_lex;
	cool = 1;
	while (current)
	{
		if (cool == 1 && current->type == 1)
			return (0);
		else if (current->type == 1 || (current->type >= 2 && current->type <= 5))
		{
			if (ft_check_place_of_special(current) == 0)
				return (0);
		}
		else if (current->type == 0 || current->type == 6 )
		{
			if (ft_check_word_if_was_special2(current) == 0)
				return (0);
		}
		cool = 0;
		past = current;
		current = current->next;
	}
	return (1);
}
