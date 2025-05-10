#include "minishell.h"

void ft_check_str(t_token **token)
{
	t_token *current = *token;
	t_token *prev = NULL;
	t_token *tmp;

	while (current)
	{
		current->value = ft_skip_thinks(current->value);

		if (!current->value)
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
			free(tmp->value);
			free(tmp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}


char *ft_get_the_true_str(char *str)
{
    size_t i = 0;
    size_t len;
    char *new_str;
    size_t j = 0;

    if (!str)
        return NULL;

    len = strlen(str);
    while (str[i] && (str[i] == '"' || str[i] == '\''))
        i++;
    while (len > i && (str[len - 1] == '"' || str[len - 1] == '\''))
        len--;

    new_str = malloc(len - i + 1);
    if (!new_str)
        return NULL;

    while (i < len)
        new_str[j++] = str[i++];
    new_str[j] = '\0';
    free(str);
    return new_str;
}

char *ft_skip_thinks(char *str)
{
	int i;
	int cool_double;
	int cool_single;

	i = 0;
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
		return (str);
    return (ft_get_the_true_str(str));
}