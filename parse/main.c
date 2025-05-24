#include "minishell.h"

int	valide_requirements(void)
{
	char	*res;

	if (!isatty(STDIN_FILENO))
	{
		error("minishell: minishell run only in a tty", 0, 0, 0);
		return (1);
	}
	res = getcwd(NULL, 0);
	if (!res)
	{
		error("minishell: minishell cannot run in orphan path", 0, 0, 0);
		return (1);
	}
	free(res);
	return (0);
}

void	prepare_requirements(t_shell *shell, char **env)
{
	tcgetattr(STDIN_FILENO, &shell->term);
	get_shell(shell, 1);
	extract_env(shell, env);
	set_last_status(&shell->last_status, 0);
	rl_catch_signals = 0;
}

int main(int ac, char **av, char **env)
{
	t_token **head_lex;
	t_main	**head;
	char	*str;

	(void)ac;
	(void)av;
	if (valide_requirements())
		return (1);
	t_shell *shell = malloc(sizeof(t_shell));
	ft_memset(shell, 0, sizeof(t_shell));
	prepare_requirements(shell, env);
	while (1)
	{
		signal(SIGINT, cntrlc);
		signal(SIGQUIT, SIG_IGN);
		shell->is_pipe = 0;
		head_lex = (t_token **) malloc(sizeof(t_token*));
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
		ft_free(str, 0);
		add_history(str);
		lexer(str, head_lex);
		ft_check_str(head_lex);
		ft_check_syntax_error(*head_lex);
		signal(SIGINT, SIG_IGN);
		ft_parsing(head_lex, head);
		signal(SIGINT, cntrlc);
		if (!*head)
		{
			my_clean();
			continue ;
		}
		 if (!(*head)->next)
			shell->last_status =  run_single_cmd(*head, shell);
		else
		{
			shell->is_pipe = 1;
			shell->last_status =  run_multi_cmd(*head, shell);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->term);
		printf("exit status: %d\n", shell->last_status);
		my_clean();
	}
}
