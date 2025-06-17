/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:58:51 by aouanni           #+#    #+#             */
/*   Updated: 2025/06/17 15:33:57 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_logique(t_main **head, t_shell *shell)
{
	if (!(*head)->next)
		shell->last_status = run_single_cmd(*head, shell);
	else
	{
		shell->is_pipe = 1;
		shell->last_status = run_multi_cmd(*head, shell);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term);
	my_clean();
}

int	parse_logique(t_token **head_lex, t_main **head, t_shell *shell)
{
	if (ft_check_syntax_error(*head_lex) == 0)
	{
		shell->last_status = 258;
		ft_exit_syntax_error();
	}
	else if (*head_lex)
	{
		signal(SIGINT, parse_protection);
		ft_check_val(head_lex, shell);
		ft_check_str_variable(head_lex);
		ft_check_str(head_lex);
		ft_make_org_var(head_lex);
		ft_parsing(head_lex, head, shell);
		if (!*head)
		{
			my_clean();
			shell->last_status = 0;
			return (1);
		}
		execution_logique(head, shell);
	}
	return (0);
}

int	main_logique(t_shell *shell, t_token **head_lex, t_main **head, char *str)
{
	head_lex = (t_token **)ft_malloc(sizeof(t_token *));
	*head_lex = NULL;
	head = (t_main **)ft_malloc(sizeof(t_main *));
	*head = NULL;
	str = readline("minishel>$ ");
	if (g_signal == SIGINT)
		shell->last_status = 1;
	g_signal = 0;
	if (!str)
	{
		ft_putstr_fd("exit\n", 2);
		my_exit(shell->last_status);
	}
	if (!str[0])
	{
		free(str);
		return (1);
	}
	ft_free(str, 0);
	add_history(str);
	lexer(str, head_lex);
	if (parse_logique(head_lex, head, shell))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_token	**head_lex;
	t_main	**head;
	char	*str;
	t_shell	*shell;

	head_lex = NULL;
	head = NULL;
	str = NULL;
	(void)ac;
	(void)av;
	if (valide_requirements())
		return (1);
	shell = malloc(sizeof(t_shell));
	ft_memset(shell, 0, sizeof(t_shell));
	prepare_requirements(shell, env);
	while (1)
	{
		shell->is_pipe = 0;
		if (main_logique(shell, head_lex, head, str))
			continue ;
	}
}
