#include "minishell.h"

static int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static int	count_words(const char *s, char sep)
{
	int i = 0, count = 0;
	int in_quote = 0;
	char quote_type = 0;

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

static char	*word_dup(const char *s, int start, int end)
{
	char	*word = malloc(end - start + 1);
	int		i = 0;

	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	*free_all(char **arr, int words)
{
	while (words--)
		free(arr[words]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char sep)
{
	char	**result;
	int		i = 0, j = 0, start;
	int		in_quote = 0;
	char	quote_type = 0;
	int		nbr_words = count_words(s, sep);

	result = malloc(sizeof(char *) * (nbr_words + 1));
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
		if (!result[j - 1])
			return (free_all(result, j - 1));
	}
	result[j] = NULL;
	return (result);
}

char	**ft_free_1(int word, char **s2)
{
	int	i;

	i = 0;
	while (i < word)
		free(s2[i++]);
	free(s2);
	return (NULL);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

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


size_t ft_strlen (char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


t_main	*ft_lstnew()
{
	t_main	*p;

	p = (t_main *) malloc(sizeof(t_main));
	if (!p)
		return (NULL);
	p->cmd = NULL;
	p->redir = NULL;
	p->is_builtin = 0;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_back(t_main **lst, t_main *new)
{
	t_main	*p;

	p = NULL;
	if (!new || !lst)
		return ;
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
				return ;
			}
			else
				p = p->next;
		}
	}
}

char	*parse_strdup(const char *s1)
{
	int		i;
	char	*p;

	p = (char *) malloc((ft_strlen((char *) s1) + 1) * sizeof(char));
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

void ft_free_cmd(char **cmd)
{
	size_t i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

void free_main_list(t_main *head)
{
	t_main *tmp_main;
	t_file *file;
	t_file *tmp_file;
	int i;

	while (head)
	{
		tmp_main = head->next;
		if (head->cmd)
		{
			i = 0;
			while (head->cmd[i])
			{
				free(head->cmd[i]);
				i++;
			}
			free(head->cmd);
		}
		file = head->redir;
		while (file)
		{
			tmp_file = file->next;
			free(file->file);
			free(file);
			file = tmp_file;
		}

		free(head);
		head = tmp_main;
	}
}


// void    ft_free(void *ptr, int flag)
// {
//     static void    *lst[INT_MAX];
//     static int    i;
//     int            j;

//     if (flag)
//     {
//         j = 0;
//         while (lst[j])
//             free(lst[j++]);
//     }
//     else
//         lst[i++] = ptr;
// }

// void    ft_exit(void)
// {
//     ft_free(NULL, 1);
//     exit(1);
// }

// void    *ft_malloc(size_t n)
// {
//     void    *ptr;

//     ptr = malloc(n);
//     if (!ptr)
//         ft_exit();
//     ft_free(ptr, 0);
//     return (ptr);
// }

// void	ft_free(void *ptr, int flag)
// {
// 	static void	*lst[INT_MAX];
// 	static int	i;
// 	int			j;

// 	if (flag)
// 	{
// 		j = 0;
// 		while (j < i && lst[j])
// 		{
// 			free(lst[j]);
// 			lst[j] = NULL;
// 			j++;
// 		}
// 		i = 0;
// 	}
// else
// 	lst[i++] = ptr;
// }

// void	my_clean(void)
// {
// 	ft_free(NULL, 1);
// }

// void	my_exit(status)
// {
// 	t_shell	*shell;
// 	t_env	*env;
// 	t_env	*next;

// 	ft_free(NULL, 1);
// 	shell = get_shell(NULL);
// 	env = shell->env;
// 	while (env)
// 	{
// 		next= env->next;
// 		free(env->key);
// 		free(env->value);
// 		free(env);
// 		env = next;
// 	}
// 	free(shell);
// 	exit(status);
// }

// void	*ft_malloc(size_t n)
// {
// 	void	*ptr;

// 	ptr = malloc(n);
// 	if (!ptr)
// 		my_exit(1);
// 	ft_free(ptr, 0);
// 	return (ptr);
// }
