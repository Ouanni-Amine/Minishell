#include "minishell.h"

int check_str(char *val)
{
	size_t	i;

	i = 0;
	while (val[i])
	{
		if (val[i] == '\"' || val[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

int ft_check_expand(char *val)
{
	if (check_str(val))
	{
		return (1);
	}
	return (0);
}

int ft_check_content(char *val, int type, t_env *env, t_shell *shell)
{
	size_t	i;
	char *str;

	i = 0;
	str = NULL;
	if (type == 6)
	{
		str = ft_add_val_in(val, env, shell);
		if(count_words2(str, ' ') != 1)
		{
			return (1);
		}
	}
	return (0);
}

size_t ft_len_droped_spaces(char *str)
{
	size_t	i;
	size_t	len;
	size_t	count;

	len = 0;
	i = 0;
	count = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		(i++, len++);
	return (len);
}

t_file *create_file_node(t_token *token, t_env *env, t_shell *shell)
{
	t_file *new_file = ft_malloc(sizeof(t_file));

	if (!new_file)
		return NULL;
	new_file->token = token->type;
	new_file->file = parse_strdup(ft_get_the_true_str3(token->next->value));
	new_file->here_doc = -1;
	if (token->type == HEREDOC && token->next->value && ft_check_expand(token->next->value))
	{
		new_file->expand = 1;
	}
	else
	{
		new_file->expand = 0;
	}
	if ((token->type == REDIR_IN || token->type == REDIR_OUT) && token->next->value && ft_check_content(token->next->value, token->next->type, env, shell))
	{
		new_file->ambiguous = 1;
	}
	else
	{
		if (new_file->expand == 0 && token->type != HEREDOC && token->next && token->next->type == 6)
		{
			new_file->file = ft_get_the_true_str3(ft_strtrim(ft_add_val_in(token->next->value, env, shell), " "));
		}
		new_file->ambiguous = 0;
	}
	new_file->next = NULL;
	return (new_file);
}

void append_file(t_file **file_head, t_file *new_file)
{
	t_file *temp;

	if (!*file_head)
	{
		*file_head = new_file;
		return ;
	}
	temp = *file_head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_file;
}

void ft_append_in_file_struct(t_token **current_token, t_file **file_head, t_env *env, t_shell *shell)
{
	t_file *new_file;

	if (!*current_token || !(*current_token)->next)
		return;
	new_file = create_file_node(*current_token, env, shell);
	if (!new_file)
		return;
	append_file(file_head, new_file);

	*current_token = (*current_token)->next->next;
}

size_t ft_count_word_token(t_token *current)
{
	size_t count = 0;

	while (current && current->type != PIPE)
	{
		if (current->type == WORD || current->type == VARIABLE || current->type == EXPORT_VAL || current->type == JUST_EXPORT)
			count++;
		else if (current->type >= REDIR_IN && current->type <= HEREDOC)
			current = current->next;
		current = current->next;
	}
	return count;
}


void	ft_append_in_main_struct(t_main *current_main, t_token **current_token, size_t *cmd_index)
{
	if (!current_main || !current_main->cmd || !current_token || !*current_token)
		return;

	current_main->cmd[*cmd_index] = parse_strdup((*current_token)->value);
	(*cmd_index)++;
	*current_token = (*current_token)->next;
}

int ft_check_if_is_built(char *value)
{
	if (!value)
		return (0);
	if (!ft_strcmp(value, "echo"))
		return (1);
	else if (!ft_strcmp(value, "cd"))
		return (1);
	else if (!ft_strcmp(value, "pwd"))
		return (1);
	else if (!ft_strcmp(value, "export"))
		return (1);
	else if (!ft_strcmp(value, "unset"))
		return (1);
	else if (!ft_strcmp(value, "env"))
		return (1);
	else if (!ft_strcmp(value, "exit"))
		return (1);
	return (0);
}

void ft_parsing(t_token **head_lex, t_main **head, t_env *env, t_shell *shell)
{
	t_token *current_token = *head_lex;
	t_main *current_main = NULL;
	t_file *file_head = NULL;
	size_t cmd_index = 0;
	size_t cmd_count;


	while (current_token)
	{
		if (!current_main)
		{
			current_main = ft_lstnew();
			if (!current_main)
				return;
			ft_lstadd_back(head, current_main);
			file_head = NULL;
			cmd_index = 0;
			cmd_count = ft_count_word_token(current_token);
			current_main->cmd = ft_malloc(sizeof(char *) * (cmd_count + 1));
			if (!current_main->cmd)
				return;
		}
		if (current_token->type >= REDIR_IN && current_token->type <= HEREDOC)
		{
			ft_append_in_file_struct(&current_token, &file_head, env, shell);
			current_main->redir = file_head;
		}
		else if (current_token->type == WORD || current_token->type == VARIABLE || current_token->type == EXPORT_VAL || current_token->type == JUST_EXPORT)
		{
			ft_append_in_main_struct(current_main, &current_token, &cmd_index);
		}
		else if (current_token->type == PIPE)
		{
			current_main->cmd[cmd_index] = NULL;
			current_main = NULL;
			current_token = current_token->next;
		}
		else
			current_token = current_token->next;
	}
	if (current_main)
		current_main->cmd[cmd_index] = NULL;
	current_main = *head;
	while (current_main)
	{
		if (current_main->cmd[0] && ft_check_if_is_built(current_main->cmd[0]))
		{
			current_main->is_builtin = 1;
		}
		current_main = current_main->next;
	}
}
