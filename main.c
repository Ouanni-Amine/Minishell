#include "builtin.h"

// t_main	*mini_parse(char *line)
// {
// 	t_main *main= ft_malloc(sizeof(t_main));
// 	main->next = NULL;
// 	main->redir = NULL;
// 	main->cmd = ft_split(line, ' ');
// 	main->is_builtin = 0;
// 	if (!(ft_strcmp(main->cmd[0], "echo") &&  ft_strcmp(main->cmd[0], "cd") && ft_strcmp(main->cmd[0], "export")
// 		&& ft_strcmp(main->cmd[0], "exit") && ft_strcmp(main->cmd[0], "pwd")
// 		&& ft_strcmp(main->cmd[0], "unset") && ft_strcmp(main->cmd[0], "env")))
// 		main->is_builtin = 1;
// 	return (main);
// }

// int main(int c, char **v, char **env)
// {
// 	t_shell *head = NULL;

// 	extract_env(&head->env, env);
// 	while (1)
// 	{
// 		char *line = readline("Minishell>");
// 		if (!line)
// 			break;
// 		t_main *main=mini_parse(line);
// 		if (!main->next)
// 			run_single_cmd(main, head);
// 		else
// 			printf("command not found\n");
// 	}
// }


t_token_type get_token_type(char *str)
{
    if (!str)
        return TOKEN_WORD;
    if (!ft_strcmp(str, "|"))
        return TOKEN_PIPE;
    if (!ft_strcmp(str, "<"))
        return TOKEN_REDIR_IN;
    if (!ft_strcmp(str, ">"))
        return TOKEN_REDIR_OUT;
    if (!ft_strcmp(str, ">>"))
        return TOKEN_REDIR_APPEND;
    if (!ft_strcmp(str, "<<"))
        return TOKEN_REDIR_HEREDOC;
    if (str[0] == '$')
        return TOKEN_ENV_VAR;
    return TOKEN_WORD;
}

int is_builtin(char *cmd)
{
    if (!cmd)
        return 0;
    return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
            !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "exit") ||
            !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "unset") ||
            !ft_strcmp(cmd, "env"));
}

void add_redir(t_file **redir_list, char *file, t_token_type type)
{
    t_file *new_redir = ft_malloc(sizeof(t_file));
    t_file *current;

    new_redir->file = ft_strdup(file, '\0');
    new_redir->token = type;
    new_redir->next = NULL;

    if (!*redir_list)
    {
        *redir_list = new_redir;
        return;
    }

    current = *redir_list;
    while (current->next)
        current = current->next;
    current->next = new_redir;
}

t_main *mini_parse(char *line)
{
    t_main *head = NULL;
    t_main *current = NULL;
    char **tokens;
    int i = 0;

    if (!line)
        return NULL;

    tokens = ft_split(line, ' ');
    if (!tokens)
        return NULL;

    // Keep processing tokens until we've gone through them all
    while (tokens[i])
    {
        // Create a new command structure
        t_main *new_cmd = ft_malloc(sizeof(t_main));
        if (!new_cmd)
            return head; // Handle malloc failure (you might want better cleanup)

        new_cmd->next = NULL;
        new_cmd->redir = NULL;

        int cmd_index = 0;
        int cmd_capacity = 10; // Initial capacity
        new_cmd->cmd = ft_malloc(sizeof(char *) * (cmd_capacity + 1));
        if (!new_cmd->cmd)
            return head; // Handle malloc failure

        // Link the new command to our list
        if (!head)
        {
            head = new_cmd;
            current = head;
        }
        else
        {
            current->next = new_cmd;
            current = new_cmd;
        }

        // Process tokens for this command (until pipe or end)
        while (tokens[i] && get_token_type(tokens[i]) != TOKEN_PIPE)
        {
            t_token_type type = get_token_type(tokens[i]);

            if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT ||
                type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC)
            {
                // Handle redirection - check if next token exists
                if (tokens[i+1])
                {
                    add_redir(&current->redir, tokens[i+1], type);
                    i += 2; // Skip redirection token and filename
                }
                else
                {
                    // Error: redirection without a file
                    i++;
                    break; // Exit the loop to prevent accessing beyond array
                }
            }
            else
            {
                // Regular command word
                if (cmd_index >= cmd_capacity)
                {
                    // Expand capacity if needed
                    cmd_capacity *= 2;
                    char **temp = realloc(current->cmd, sizeof(char *) * (cmd_capacity + 1));
                    if (!temp) {
                        // Handle realloc failure
                        break;
                    }
                    current->cmd = temp;
                }
                current->cmd[cmd_index++] = ft_strdup(tokens[i], '\0');
                if (!current->cmd[cmd_index-1]) {
                    // Handle strdup failure
                    break;
                }
                i++;
            }
        }

        // Null-terminate the command array
        current->cmd[cmd_index] = NULL;

        // Check if the command is a builtin
        current->is_builtin = (cmd_index > 0 && current->cmd[0]) ? is_builtin(current->cmd[0]) : 0;

        // If current token is a pipe, move past it for the next command
        if (tokens[i] && get_token_type(tokens[i]) == TOKEN_PIPE)
            i++;
    }

    // Clean up original token array
    for (i = 0; tokens[i]; i++)
        free(tokens[i]);
    free(tokens);

    return head;
}

int main(int argc, char **argv, char **env)
{
    t_shell *head = ft_malloc(sizeof(t_shell));
    head->env = NULL;
    head->last_status = 0;

    extract_env(&head->env, env);

    while (1)
    {
        char *line = readline("Minishell> ");
        if (!line)
            break;

        t_main *main = mini_parse(line);
        if (!main->next)
            run_single_cmd(main, head);
        else
            run_multi_cmd(main, head);
    }
    return 0;
}
