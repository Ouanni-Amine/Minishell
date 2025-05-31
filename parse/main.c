/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:58:51 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/31 15:12:07 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_lstsize(t_token *lst)
{
	size_t count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char *get_nameof_val(char *val, size_t i)
{
	size_t start;
	size_t len;
	size_t j;
	char *dest;

	start = i + 1;
	len = 0;
	j = 0;
	while (val[start + len] && ft_symbols_max(val[start + len]))
		len++;
	dest = ft_malloc(len + 1);
	while (j < len)
	{
		dest[j] = val[start + j];
		j++;
	}
	dest[len] = '\0';
	return (dest);
}

size_t	ft_len_val(char *val, size_t i, t_env *env)
{
	char	*str;

	while (val[i])
	{
		if (val[i] == '$' && val[i + 1] && val[i + 1] != ' ' && val[i + 1] != '\t' && val[i + 1] != '\'' && val[i + 1] != '"')
		{
			str = get_env_value(env, get_nameof_val(val, i));
			return (ft_strlen(str));
		}
		i++;
	}
	return (0);
}

size_t ft_fullstr_len(char *val, t_env *env)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (val[i])
	{
		if (val[i] == '$' && val[i + 1] && val[i + 1] != ' ' && val[i + 1] != '\t' && val[i + 1] != '\'' && val[i + 1] != '"')
		{
			count += ft_len_val(val, i, env);
			while (val[i] && val[i] != ' ' && val[i] != '\t')
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char *get_full_str(char *val, t_env *env)
{
	char	*full_str;
	size_t	i;
	size_t	j;
	size_t	k;
	char	*local;

	i = 0;
	j = 0;
	k = 0;
	full_str = ft_malloc(sizeof(char) * (ft_fullstr_len(val, env) + 1));
	while (val[i])
	{
		if (val[i] == '$' && val[i + 1] && val[i + 1] != ' ' && val[i + 1] != '\t' && val[i + 1] != '\'' && val[i + 1] != '"')
		{
			j = 0;
			local = get_env_value(env, get_nameof_val(val, i));
			while (local[j])
				full_str[k++] = local[j++];
		}
		else
			full_str[k++] = val[i++];
	}
	full_str[k] = '\0';
	return (full_str);
}

int ft_symbols_max(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	if (c == '?' || c == '$')
		return (0);
	return (0);
}

int ft_symbols(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_' || c == '?' ) // || c == '$'
		return (1);
	return (0);
}

void ft_add_val_len_norm(char *val, t_env *env, t_shell *shell, t_norm *norm, char *local)
{
	while (val[(*norm).i])
	{
		if (val[(*norm).i] == '$' && val[(*norm).i + 1] && val[(*norm).i + 1] == '?')
		{
			local = ft_itoa(shell->last_status);
			(*norm).j = 0;
			(*norm).len += ft_strlen(local);
			(*norm).i += 2;
			continue;
		}
		else if (val[(*norm).i] == '$' && val[(*norm).i + 1] && ((val[(*norm).i + 1] >= '0' && val[(*norm).i + 1] <= '9') )) // || val[i + 1] == '$' || val[i + 1] == '_'
		{
			(local = "", (*norm).i += 2);
			continue;
		}
		else if (val[(*norm).i] == '$' && val[(*norm).i + 1] && ft_symbols_max(val[(*norm).i + 1]))
		{
			local = change_quotes(ft_strdup(get_env_value(env, get_nameof_val(val, (*norm).i)), '\0'));
			if (local)
				(*norm).len += ft_strlen(local);
			(*norm).i += ft_strlen(get_nameof_val(val, (*norm).i)) + 1;
		}
		else
			((*norm).len++, (*norm).i++);
	}
}

void ft_add_val_str_norm_special(t_norm *norm, t_shell *shell, char *full_str)
{
	char *local;

	local = NULL;
	local = ft_itoa(shell->last_status);
	(*norm).j = 0;
	while (local[(*norm).j])
		full_str[((*norm).k)++] = local[((*norm).j)++];
	(*norm).i += 2;
}

void ft_add_val_str_norm_simple(t_env *env, t_norm *norm, char *val, char *full_str)
{
	char *local;

	local = change_quotes(ft_strdup(get_env_value(env, get_nameof_val(val, (*norm).i)), '\0'));
	if (local)
	{
		(*norm).j = 0;
		while (local[(*norm).j])
			full_str[((*norm).k)++] = local[((*norm).j)++];
	}
	(*norm).i += ft_strlen(get_nameof_val(val, (*norm).i)) + 1;
}

void ft_add_val_str_norm(char *val, t_norm *norm, t_shell *shell, t_env *env, char *full_str)
{
	char *local;

	local = NULL;
	while (val[(*norm).i])
	{
		if (val[(*norm).i] == '$' && val[(*norm).i + 1] && val[(*norm).i + 1] == '?')
		{
			ft_add_val_str_norm_special(norm, shell, full_str);
			continue;
		}
		else if (val[(*norm).i] == '$' && val[(*norm).i + 1] && ((val[(*norm).i + 1] >= '0' && val[(*norm).i + 1] <= '9'))) // || val[i + 1] == '$' || val[i + 1] == '_'
		{
			local = "";
			(*norm).i += 2;
			continue;
		}
		if (val[(*norm).i] == '$' && val[(*norm).i + 1] && ft_symbols_max(val[(*norm).i + 1]))
			ft_add_val_str_norm_simple(env, norm, val, full_str);
		else
			full_str[(*norm).k++] = val[(*norm).i++];
	}
	full_str[(*norm).k] = '\0';
}

char *ft_add_val_in(char *val, t_env *env, t_shell *shell)
{
	char *full_str;
	t_norm norm;
	char *local;

	norm.i = 0;
	norm.k = 0;
	norm.len = 0;
	norm.j = 0;
	if (!val)
		return (NULL);
	ft_add_val_len_norm(val, env, shell, &norm, local);
	full_str = ft_malloc(norm.len + 1);
	(norm.i = 0, norm.k = 0);
	ft_add_val_str_norm(val, &norm, shell, env, full_str);
	return (full_str);
}

int ft_isspaces_inside(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

size_t ft_get_len(char *str)
{
	size_t i;
	size_t len;
	char quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			len++;
		i++;
	}
	return (len);
}

char *ft_check_hard_str(char *str)
{
	size_t i;
	size_t j;
	size_t len;
	char *new_str;
	char quote;

	i = 0;
	j = 0;
	len = ft_get_len(str);
	new_str = ft_malloc(sizeof(char) * (len + 1));
	quote = 0;
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

t_token *ft_build_token(char *str)
{
	t_token	*new_token;

	new_token = ft_malloc(sizeof(t_token));
	new_token->next = NULL;
	new_token->type = EXPORT_VAL;
	new_token->value = ft_strdup(str, 0);
	return (new_token);
}

t_token	*ft_add_token(t_token *current)
{
	char	**new_str;
	t_token	*org;
	t_token	*current_next;
	size_t	i;
	t_token	*new_token;

	i = 0;
	new_str = ft_split(current->value, ' ');
	if (!new_str[0])
		return (NULL);
	current_next = current->next;
	org = current;
	current->value = new_str[i++];
	current->type = EXPORT_VAL;
	while (new_str[i])
	{
		new_token = ft_build_token(new_str[i]);
		current->next = new_token;
		current = current->next;
		i++;
	}
	if (current_next)
		current->next = current_next;
	return (org);
}

int ft_check_key(char *str)
{
	size_t	i;
	size_t	cool;

	i = 0;
	cool = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			cool++;
			i++;
		}
		else if (str[i] >= 'a' && str[i] <= 'z')
			i++;
		else if ((str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
			i++;
		else
			return (0);
	}
	if (cool > 1)
		return (0);
	return (1);
}

int ft_if_key_valid(char *val)
{
	if (ft_check_key(ft_strdup_updated(val, '=')))
		return (1);
	return (0);
}

t_token *ft_check_val_norm_max(t_norm *norm, t_token *current, t_env *env, t_shell *shell)
{
	current->value = ft_add_val_in(current->value, env, shell);
	current = ft_add_token(current);
	(norm->past = current, current = norm->next);
	return (current);
}

t_token *ft_check_val_norm(t_norm *norm, t_token *current, t_env *env,
							t_shell *shell, t_token **token)
{
	if (norm->past != NULL && norm->past->type == HEREDOC && current->type == VARIABLE)
		(norm->past = current, current = norm->next);
	else if (norm->past != NULL && (norm->past->type == REDIR_IN || norm->past->type == REDIR_OUT) && current->type == VARIABLE)
		(norm->past = current, current = norm->next);
	else if (norm->past && norm->past->type == JUST_EXPORT && current->type == VARIABLE)
		current = ft_check_val_norm_max(norm, current, env, shell);
	else if (!ft_strcmp((*token)->value, "export") && (*token)->type == VARIABLE && ft_if_key_valid(current->value) && current->type == VARIABLE)
		current = ft_check_val_norm_max(norm, current, env, shell);
	else if (!ft_strcmp((*token)->value, "export") && ft_if_key_valid(current->value))
	{
		current->value = ft_add_val_in(current->value, env, shell);
		(norm->past = current, current = norm->next);
	}
	else if (current->type == VARIABLE || current->type == EXPORT_VAL)
	{
		current->value = ft_add_val_in(current->value, env, shell);
		if (ft_isspaces_inside(current->value))
			current = ft_add_token(current);
		(norm->past = current, current = norm->next);
	}
	else
		(norm->past = current, current = norm->next);
	return (current);
}

void ft_check_val(t_token **token, t_env *env, t_shell *shell)
{
	t_token *current;
	t_norm norm;

	current = *token;
	norm.past = NULL;
	while (current)
	{
		norm.next = current->next;
		current = ft_check_val_norm(&norm, current, env, shell, token);
	}
}
int	valide_requirements(void)
{
	char	*res;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		ft_putstr_fd("minishell: minishell run only in a tty\n", 2);
		return (1);
	}
	res = getcwd(NULL, 0);
	if (!res)
	{
		ft_putstr_fd("minishell: minishell cannot run in orphan path\n", 2);
		return (1);
	}
	free(res);
	return (0);
}

void	prepare_requirements(t_shell *shell, char **env)
{
	char	*df_path;

	df_path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	tcgetattr(STDIN_FILENO, &shell->term);
	get_shell(shell, 1);
	extract_env(shell, env, df_path);
	set_last_status(&shell->last_status, 0);
	rl_catch_signals = 0;
}

// int main(int ac, char **av, char **env)
// {
// 	t_token **head_lex;
// 	t_main	**head;
// 	char	*str;

// 	(void)ac;
// 	(void)av;
// 	if (valide_requirements())
// 		return (1);
// 	t_shell *shell = malloc(sizeof(t_shell));
// 	ft_memset(shell, 0, sizeof(t_shell));
// 	prepare_requirements(shell, env);
// 	while (1)
// 	{
// 		signal(SIGINT, cntrlc);
// 		signal(SIGQUIT, SIG_IGN);
// 		shell->is_pipe = 0;
// 		head_lex = (t_token **)ft_malloc(sizeof(t_token *));
// 		*head_lex = NULL;
// 		head = (t_main **)ft_malloc(sizeof(t_main *));
// 		*head = NULL;
// 		str = readline("minishel>$ ");
// 		if (!str)
// 		{
// 			ft_putstr_fd("exit\n", 1);
// 			my_exit(shell->last_status);
// 		}
// 		if (!str[0])
// 		{
// 			free(str);
// 			continue;
// 		}
// 		ft_free(str, 0);
// 		add_history(str);
// 		lexer(str, head_lex);
// 		if (ft_check_syntax_error(*head_lex) == 0)
// 		{
// 			shell->last_status = 258;
// 			ft_exit_syntax_error();
// 		}
// 		else if (*head_lex)
// 		{
// 			signal(SIGINT, SIG_IGN);
// 			ft_check_val(head_lex, shell->env, shell);
// 			ft_check_str_variable(head_lex);
// 			ft_check_str(head_lex);
// 			ft_make_org_var(head_lex);
// 			ft_parsing(head_lex, head, shell->env, shell);
// 			if (!*head)
// 			{
// 				my_clean();
// 				continue ;
// 			}
// 			if (!(*head)->next)
// 				shell->last_status =  run_single_cmd(*head, shell);
// 			else
// 			{
// 				shell->is_pipe = 1;
// 				shell->last_status =  run_multi_cmd(*head, shell);
// 			}
// 			tcsetattr(STDIN_FILENO, TCSANOW, &shell->term);
// 			my_clean();
// 		}
// 	}
// }

void	execution_logique(t_main **head, t_shell *shell)
{
	if (!(*head)->next)
		shell->last_status = run_single_cmd(*head, shell);
	else
	{
		shell->is_pipe = 1;
		shell->last_status =  run_multi_cmd(*head, shell);
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
		signal(SIGINT, SIG_IGN);
		ft_check_val(head_lex, shell->env, shell);
		ft_check_str_variable(head_lex);
		ft_check_str(head_lex);
		ft_make_org_var(head_lex);
		ft_parsing(head_lex, head, shell->env, shell);
		if (!*head)
		{
			my_clean();
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

	(void)ac;
	(void)av;
	if (valide_requirements())
		return (1);
	shell = malloc(sizeof(t_shell));
	ft_memset(shell, 0, sizeof(t_shell));
	prepare_requirements(shell, env);
	while(1)
	{
		signal(SIGINT, cntrlc);
		signal(SIGQUIT, SIG_IGN);
		shell->is_pipe = 0;
		if (main_logique(shell, head_lex, head, str))
			continue ;
	}
}
