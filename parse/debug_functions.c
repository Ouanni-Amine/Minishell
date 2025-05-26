#include "minishell.h"

void	print_file_list(t_file *head)
{
	while (head)
	{
		printf("        token = %s\n",
			head->token == REDIR_IN ? "REDIR_IN" :
			head->token == REDIR_OUT ? "REDIR_OUT" :
			head->token == REDIR_APPEND ? "REDIR_APPEND" :
			head->token == HEREDOC ? "HEREDOC" :
			head->token == VARIABLE ? "VARIABLE" : "UNKNOWN");
		printf("        file = \"%s\"\n", head->file);
		printf("        herdoc = \"%d\"\n", head->here_doc);
		printf("        expand = \"%d\"\n", head->expand);
		printf("        ambiguous = \"%d\"\n", head->ambiguous);
		if (head->next)
			printf("        next →\n");
		else
			printf("        next = NULL\n");
		head = head->next;
	}
}

void	print_main_debug(t_main *head)
{
	int i = 0;

	while (head)
	{
		printf("t_main {\n");
		printf("    cmd = [");
		if (head->cmd)
		{
			while (head->cmd[i])
			{
				printf("%s", head->cmd[i]);
				if (head->cmd[i + 1])
					printf(", ");
				i++;
			}
		}
		printf(", NULL]\n");
		if (head->redir == NULL)
			printf("    head = NULL  // no redirection\n");
		else
		{
			printf("    head = t_file {\n");
			print_file_list(head->redir);
			printf("    }\n");
		}
		printf ("	built_in = %d\n", head->is_builtin);
		if (head->next)
			printf("    next →\n");
		else
			printf("    next = NULL\n");
		printf("}\n\n");
		head = head->next;
		i = 0;
	}
}


void	print_tokens(t_token *head)
{
	t_token *current = head;

	// current = NULL;
	if (current == NULL)
		printf ("error\n") ;
	else if (current->value[0] == '\0')
		printf ("error go go go\n");
	while (current)
	{
		printf("Value: [%s], Type: [%u]\n", current->value, current->type);
		current = current->next;
	}
}