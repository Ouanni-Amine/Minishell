#include "minishell.h"

// char *ft_get_key(char *str)
// {
// 	if (str[0] == '$')
// 	{
// 		return (str + 1);
// 	}
// 	else if (ft_strcmp("export", str))
// 	{
// 		// get the next tokens
// 		// check inside it if the variable is invalid if not split it with spaces
// 	}
// }

// void ft_check_val(t_token *token, t_env *env)
// {
// 	while (token)
// 	{
// 		if (token->type == 6)
// 		{
// 			if (token->value[0] == '$')
// 			{
// 				token->value = get_env_value(env, ft_get_key(token->value));
// 			}
// 		}
// 	}
// }


int main(int ac, char **av, char **env)
{
	t_token **head_lex;
	t_main	**head;
	if (!isatty(STDIN_FILENO))
	{
		error("minishell: minishell run only in a ttu", 0, 0, 0);
		return (1);
	}
	char *res = getcwd(NULL, 0);
	if (!res)
	{
		error("minishell: minishell cannot run in orphan path", 0, 0, 0);
		return (1);
	}
	free(res);
	t_shell *shell = malloc(sizeof(t_shell));
	char *str;
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);//NOTE: i captured the original bash settings
    shell->env = NULL;
    shell->last_status = 0;
	shell->pwd_emergcy = NULL;
	get_shell(shell, 1);
	extract_env(&shell->env, env);
	set_last_status(&shell->last_status, 0);
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, cntrlc);
		signal(SIGQUIT, SIG_IGN);
		shell->is_pipe = 0;
		head_lex = (t_token **) malloc (sizeof(t_token*));
		if (!head_lex)
			return (0);
		*head_lex = NULL;
		head = (t_main **) malloc(sizeof(t_main *));
		if (!head)
			return (0);
		*head = NULL;
		str = readline("minishel>$ ");
		if (!str)
		{
			ft_putstr_fd("exit\n", 1);
			my_exit(shell->last_status);
		}
		ft_free(str, 0);//NOTE: valide this or just call free(line) at the end
		lexer(str, head_lex);
		ft_check_str(head_lex);
		ft_check_syntax_error(*head_lex);
		// print_tokens(*head_lex);
		// ft_check_val(*head_lex, env_head);
		signal(SIGINT, SIG_IGN);//note :in case the paring will take long time;
		ft_parsing(head_lex, head);
		signal(SIGINT, cntrlc);
		if (!*head)//NOTE: i added this cause i got a segfault when i did tab and enter
			continue ;
		 if (!(*head)->next)
			shell->last_status =  run_single_cmd(*head, shell);
		else
		{
			shell->is_pipe = 1;
			shell->last_status =  run_multi_cmd(*head, shell);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &term);//NOTE: i restore them
		printf("last status is ==> %d\n", shell->last_status);
		my_clean();
	}
}
