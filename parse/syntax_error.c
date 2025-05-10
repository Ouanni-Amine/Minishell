#include "minishell.h"

void ft_check_place_of_special(t_token *current)
{
	if (!current->next)
		ft_exit_syntax_error();
	if ((current->type >= 2 && current->type <= 5) && current->next->type == 1)
		ft_exit_syntax_error();
	else if (current->type == current->next->type)
		ft_exit_syntax_error();
}

void ft_check_word_if_was_special(t_token *current)
{
	char *str;
	int i;
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
	// printf ("%d\n", cool);
	if (cool_double % 2 != 0 || cool_single % 2 != 0)
		ft_exit_syntax_error();
}

void ft_exit_syntax_error()
{
	printf ("syntax error\n");
	// free_tokens();
	exit (2);
	// ft_exit();
}

void ft_check_syntax_error(t_token *head_lex)
{
	t_token *current;
	int cool;

	current = head_lex;
	cool = 1;
	while (current)
	{
		// && (current->type == 1 || (current->type >= 2 && current->type <= 5))
		if (cool == 1 && current->type == 1)
		{
			ft_exit_syntax_error();
		}
		else if (current->type == 1 || (current->type >= 2 && current->type <= 5))
		{
			ft_check_place_of_special(current);
		}
		else if (current->type == 0)
		{
			ft_check_word_if_was_special(current);
		}
		// TODO for handle the advanced case of the "" && '' i should be use math like / && %
		cool = 0;
		// todo i should be add the check of variables
		current = current->next;
	}
}
