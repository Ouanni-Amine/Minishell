#include "minishell.h"

size_t	ft_count_str_with_space(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
			(count+=4, i+=2);
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			(count+=3, i++);
		else
			(count++,i++);
	}
	return (count);
}

char *ft_make_str_with_space(char *str)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*new_str;
	char	in_quote;

	len = ft_count_str_with_space(str);
	i = 0;
	j = 0;
	new_str = (char *) ft_malloc(sizeof(char) * (len + 1));
	in_quote = 0;
	while (str[i])
	{
		if (!in_quote && (str[i] == '\'' || str[i] == '"'))
		{
			in_quote = str[i];
			new_str[j++] = str[i++];
		}
		else if (!in_quote)
		{
			if (str[i] == '>' && str[i + 1] == '>')
				(new_str[j++] = ' ', new_str[j++] = '>', new_str[j++] = '>', new_str[j++] = ' ', i+=2);
			else if (str[i] == '<' && str[i + 1] == '<')
				(new_str[j++] = ' ', new_str[j++] = '<', new_str[j++] = '<', new_str[j++] = ' ', i+=2);
			else if (str[i] == '>')
				(new_str[j++] = ' ', new_str[j++] = '>', new_str[j++] = ' ', i++);
			else if (str[i] == '<')
				(new_str[j++] = ' ', new_str[j++] = '<', new_str[j++] = ' ', i++);
			else if (str[i] == '|')
				(new_str[j++] = ' ', new_str[j++] = '|', new_str[j++] = ' ', i++);
			else
				new_str[j++] = str[i++];
		}
		else if (in_quote && str[i] == in_quote)
		{
			in_quote = 0;
			new_str[j++] = str[i++];
		}
		else if (in_quote)
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
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
