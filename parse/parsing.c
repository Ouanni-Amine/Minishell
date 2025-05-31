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
		new_file->expand = 1;
	else
		new_file->expand = 0;
	if ((token->type == REDIR_IN || token->type == REDIR_OUT) && token->next->value && ft_check_content(token->next->value, token->next->type, env, shell))
		new_file->ambiguous = 1;
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

void ft_parsing_norm_max(t_norm *norm, t_main **head)
{
	norm->current_main = ft_lstnew();
	ft_lstadd_back(head, norm->current_main);
	norm->file_head = NULL;
	norm->cmd_index = 0;
	norm->cmd_count = ft_count_word_token(norm->current_token);
	norm->current_main->cmd = ft_malloc(sizeof(char *) * (norm->cmd_count + 1));
}

t_token *ft_parsing_norm(t_norm *norm, t_env *env, t_main **head, t_shell *shell)
{
	if (!norm->current_main)
		ft_parsing_norm_max(norm, head);
	if (norm->current_token->type >= REDIR_IN && norm->current_token->type <= HEREDOC)
	{
		ft_append_in_file_struct(&norm->current_token, &norm->file_head, env, shell);
		norm->current_main->redir = norm->file_head;
	}
	else if (norm->current_token->type == WORD || norm->current_token->type == VARIABLE ||
			norm->current_token->type == EXPORT_VAL || norm->current_token->type == JUST_EXPORT)
		ft_append_in_main_struct(norm->current_main, &norm->current_token, &norm->cmd_index);
	else if (norm->current_token->type == PIPE)
	{
		norm->current_main->cmd[norm->cmd_index] = NULL;
		norm->current_main = NULL;
		norm->current_token = norm->current_token->next;
	}
	else
		norm->current_token = norm->current_token->next;
	return (norm->current_token);
}

void ft_parsing(t_token **head_lex, t_main **head, t_env *env, t_shell *shell)
{
	t_norm norm;

	norm.current_token = *head_lex;
	norm.current_main = NULL;
	norm.file_head = NULL;
	norm.cmd_index = 0;
	while (norm.current_token)
	{
		norm.current_token = ft_parsing_norm(&norm, env, head, shell);
	}
	if (norm.current_main)
		norm.current_main->cmd[norm.cmd_index] = NULL;
	norm.current_main = *head;
	while (norm.current_main)
	{
		if (norm.current_main->cmd[0] && ft_check_if_is_built(norm.current_main->cmd[0]))
			norm.current_main->is_builtin = 1;
		norm.current_main = norm.current_main->next;
	}
}
