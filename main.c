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


int main(int c , char **v, char **env)
{
	t_env *head = NULL;

	extract_env(&head, env);
	t_main *main = malloc(sizeof(t_main));
	main->cmd = ft_malloc(sizeof(char*) * 2);
	main->redir = ft_malloc(sizeof(t_file));
	// t_file *node1 = ft_malloc(sizeof(t_file));
	// t_file *node2 = ft_malloc(sizeof(t_file));
	// node1->file = "t";
	// node1->token = 5;
	// node1->next= NULL;
	// node2->next = NULL;
	// node2->file= "out2";
	// node2->token= 3;
	main->cmd[1] = NULL;
	main->cmd[0]= "export";
	main->is_builtin = 1;
	main->next = NULL;
	main->redir->file="koka.txt";
	main->redir->token = 3;
	main->redir->next = NULL;
	run_single_cmd(main, &head);
}


// int main(int c, char **v, char **env)
// {
// 	t_env *head = NULL;

// 	extract_env(&head, env);
// 	while (1)
// 	{
// 		char *line = readline("Minishell>");
// 		if (!line)
// 			break;
// 		t_main *main=mini_parse(line);
// 		if (!main->next)
// 			run_single_cmd(main, &head);
// 	}
// }
