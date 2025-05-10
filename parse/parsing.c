#include "minishell.h"

t_file *create_file_node(t_token *token)
{
	t_file *new_file = malloc(sizeof(t_file));
	if (!new_file)
		return NULL;
	new_file->token = token->type;
	new_file->file = parse_strdup(token->next->value);
	new_file->next = NULL;
	return new_file;
}

void append_file(t_file **file_head, t_file *new_file)
{
	t_file *temp;

	if (!*file_head)
	{
		*file_head = new_file;
		return;
	}
	temp = *file_head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_file;
}

void ft_append_in_file_struct(t_token **current_token, t_file **file_head)
{
	t_file *new_file;

	if (!*current_token || !(*current_token)->next)
		return;
	new_file = create_file_node(*current_token);
	if (!new_file)
		return;
	append_file(file_head, new_file);

	*current_token = (*current_token)->next->next;
}

// size_t ft_count_word_token(t_token *current)
// {
// 	size_t count = 0;

// 	while (current && current->type != PIPE)
// 	{
// 		if (current->type == WORD)
// 			count++;
// 		else if (current->type >= REDIR_IN && current->type <= HEREDOC)
// 			current = current->next;
// 		current = current->next;
// 	}
// 	return count;
// }

size_t ft_count_word_token(t_token *current)
{
	size_t count = 0;

	while (current && current->type != PIPE)
	{
		if (current->type == WORD || current->type == VARIABLE)
			count++;
		else if (current->type >= REDIR_IN && current->type <= HEREDOC)
			current = current->next;
		current = current->next;
	}
	return count;
}



void ft_append_in_main_struct(t_main *current_main, t_token **current_token, size_t *cmd_index)
{
	current_main->cmd[*cmd_index] = parse_strdup((*current_token)->value);
	(*cmd_index)++;
	*current_token = (*current_token)->next;
}

#include <string.h>

int ft_check_if_is_built(char *value)
{
	if (!value)
		return (0);
	if (!strcmp(value, "echo"))
		return (1);
	else if (!strcmp(value, "cd"))
		return (1);
	else if (!strcmp(value, "pwd"))
		return (1);
	else if (!strcmp(value, "export"))
		return (1);
	else if (!strcmp(value, "unset"))
		return (1);
	else if (!strcmp(value, "env"))
		return (1);
	else if (!strcmp(value, "exit"))
		return (1);
	return (0);
}


// int ft_check_if_is_built(char *value)
// {
// 	if (!ft_strncmp("echo", value, 5) && ft_strlen(value) == 5)
// 		return (1);
// 	else if (!ft_strncmp("cd", value ,3) && ft_strlen(value) == 3)
// 		return (1);
// 	else if (!ft_strncmp("pwd", value ,4) && ft_strlen(value) == 4)
// 		return (1);
// 	else if (!ft_strncmp("export", value ,7) && ft_strlen(value) == 7)
// 		return (1);
// 	else if (!ft_strncmp("unset", value ,6) && ft_strlen(value) == 6)
// 		return (1);
// 	else if (!ft_strncmp("env", value ,4) && ft_strlen(value) == 4)
// 		return (1);
// 	else if (!ft_strncmp("exit", value ,5) && ft_strlen(value) == 5)
// 		return (1);
// 	return (0);
// }

void ft_parsing(t_token **head_lex, t_main **head)
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
			current_main->cmd = malloc(sizeof(char *) * (cmd_count + 1));
			if (!current_main->cmd)
				return;
		}
		if (current_token->type >= REDIR_IN && current_token->type <= HEREDOC)
		{
			ft_append_in_file_struct(&current_token, &file_head);
			current_main->redir = file_head;
		}
		else if (current_token->type == WORD || current_token->type == VARIABLE)
		{
			// printf ("1\n");
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
		// break;
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
