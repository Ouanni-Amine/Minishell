/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:37:42 by aouanni           #+#    #+#             */
/*   Updated: 2025/06/03 17:39:35 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>

volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	VARIABLE,
	EXPORT_VAL,
	JUST_EXPORT
}	t_token_type;

typedef struct s_file
{
	char			*file;
	t_token_type	token;
	int				here_doc;
	int				expand;
	int				ambiguous;
	struct s_file	*next;
}	t_file;

typedef struct s_main
{
	char			**cmd;
	t_file			*redir;
	int				is_builtin;
	struct s_main	*next;
}	t_main;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_active;
	int				rank;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env			*env;
	int				last_status;
	int				is_pipe;
	char			*pwd_emergcy;
	struct termios	term;
}	t_shell;

typedef struct s_pipex
{
	int		pipe_fd[2];
	int		prev_fd;
	int		pid[1392];
	int		last_pid;
	int		nb_cmd;
	int		diff;
}	t_pipex;

typedef struct s_norm
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	len;
	size_t	k;
	t_token	*tmp;
	t_token	*past;
	t_token	*prev;
	t_token	*next;
	t_main	*current_main;
	t_file	*file_head;
	size_t	cmd_index;
	size_t	cmd_count;
	t_token	*current_token;
	t_token	**token;
}	t_norm;

size_t		ft_get_true_len(const char *str, char c);
int			ft_find_export_word(t_token *current);
int			ft_check_variable(char *str);
size_t		ft_count_str(char *str);
char		*get_nameof_val(char *val, size_t i);
size_t		ft_len_val(char *val, size_t i, t_env *env);
size_t		ft_fullstr_len(char *val, t_env *env);
int			ft_isspaces_inside(char *str);
size_t		ft_get_len(char *str);
t_token		*ft_build_token(char *str);
t_token		*ft_add_token(t_token *current);
int			ft_check_key(char *str);
t_token		*ft_check_val_norm_max(t_norm *norm, t_token *current,
				t_shell *shell);
t_token		*ft_check_val_norm(t_norm *norm, t_token *ct,
				t_shell *shell, t_token **tk);
int			ft_check_expand(char *val);
int			ft_check_content(char *val, int type, t_shell *shell);
void		append_file(t_file **file_head, t_file *new_file);
size_t		ft_count_word_token(t_token *current);
void		ft_append_in_main_struct(t_main *current_main,
				t_token **current_token, size_t *cmd_index);
int			ft_check_if_is_built(char *value);
void		ft_parsing_norm_max(t_norm *norm, t_main **head);
t_token		*ft_parsing_norm(t_norm *norm, t_main **head, t_shell *shell);
void		ft_exit_syntax_error(void);
int			next_qt(char *str, int i, char type);
size_t		ft_true_str3_len(char *str);
char		*ft_between_cotes(char *str, char type, t_norm *norm, char *dst);
void		ft_add_val_len_norm(char *val, t_shell *shell,
				t_norm *norm, char *local);
void		ft_add_val_str_norm(char *val, t_norm *norm,
				t_shell *shell, char *full_str);
int			ft_check_variable_max(char *str, size_t index);
void		ft_set_norm1(t_norm *norm, t_token **current);
char		*ft_set_norm2(t_token *current);
t_token		*ft_set_norm3(t_norm *norm, t_token *current);
t_token		*ft_set_norm4(t_token **token, t_token	**prev, t_token	*current);
int			fquote(char c);
char		*ft_make_org_str(char *str);
void		ft_add_token_pipe(t_token **current);
void		ft_get_true_str_norm(char *new_str, t_norm *norm, char *str);
void		ft_make_spaces_norm1(char *new_str, size_t *i, size_t *j);
void		ft_make_spaces_norm2(char *new_str, size_t *i, size_t *j);
void		ft_make_spaces_norm3(char *new_str, size_t *i, size_t *j);
char		ft_make_with_space_1(char *new_str, char *str,
				char in_quote, t_norm *norm);
char		ft_make_with_space_2(char *new_str, char *str,
				char in_quote, t_norm *norm);
void		ft_code_norm1(char *local, t_shell *shell, t_norm *n);
void		ft_code_norm2(char *local, t_shell *shell, t_norm *n, char *v);
int			ft_code_norm3(t_norm *n, char *v);
char		*ft_code_norm4(t_token *tk, t_shell *shell);
int			valide_requirements(void);
void		prepare_requirements(t_shell *shell, char **env);

char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(char *str);
char		*ft_make_space(char *str);
t_main		*ft_lstnew(void);
void		ft_lstadd_back(t_main **lst, t_main *new);
int			ft_check_syntax_error(t_token *head_lex);
void		ft_exit_syntax_error(void);
void		ft_check_str(t_token **token);
char		*ft_skip_thinks(char *str, int cool);
void		ft_free(void *ptr, int flag);
void		*ft_malloc(size_t n);
size_t		ft_lstsize(t_token *lst);
void		ft_check_str_variable(t_token **token);
void		lexer(char *str, t_token **head_lex);
int			ft_symbols(char c);
char		*ft_get_the_true_str3(char *str);
char		*ft_strdup_updated(const char *s1, char c);
char		*ft_get_the_true_str2(char *str);
void		ft_check_val(t_token **token, t_shell *shell);
char		*ft_add_val_in(char *val, t_shell *shell);
t_file		*create_file_node(t_token *token, t_shell *shell);
void		ft_parsing(t_token **head_lex, t_main **head, t_shell *shell);
void		ft_append_in_file_struct(t_token **current_token,
				t_file **file_head, t_shell *shell);
int			count_words2(const char *s, char sep);
char		*ft_strtrim(char const *s1, char const *s2);
int			ft_strstr_match(const char *haystack, const char *needle);
int			ft_if_key_valid(char *val);
char		*change_quotes(char *str);
void		ft_make_org_var(t_token **head_lex);
int			ft_symbols_max(char c);

int			ft_echo(char **cmd);
int			ft_cd(char **cmd, t_shell *shell);
int			ft_pwd(t_shell *shell);
int			ft_exit(char **cmd, t_shell *shell);
int			ft_env(char **cmd, t_env *env);
int			ft_unset(t_env **head, char **cmd);
int			ft_export(t_env **env, char **cmd);

int			get_lenght(t_env *head);
void		env_add_back(t_env	**head, t_env *new);
void		env_add_back(t_env	**head, t_env *new);
void		set_env_value(t_env **head, char *key, char *value, int i);
void		sort_export(t_env **env);
void		extract_env(t_shell *shell, char **env, char *df_path);
char		*get_env_value(t_env *env, char *key);
char		**env_convertor(t_env *env);
t_env		*create_env_node(char *key, char *value, int i);
t_shell		*get_shell(t_shell *shell, int flag);

void		*ft_malloc(size_t n);
void		ft_free(void *ptr, int flag);
void		my_exit(int status);
void		my_clean(void);

int			handle_redir(t_main *main);
int			handle_redir_heredoc(t_main *main, t_shell *shell);
int			heredoc_inputfd(t_file *current, t_shell *shell);
int			here_doc_count(t_main *main);
int			run_multi_cmd(t_main *main, t_shell *shell);
int			run_builtins(t_main *main, t_shell *shell);
int			run_single_cmd(t_main *main, t_shell *shell);
int			parent_exit(t_pipex *pipex, t_main *main);
void		heredoc_cleanup(t_main *main);
void		sig_handler(int signal);
void		parse_protection(int signal);
void		prepare_signals(void);
void		change_handler(int code);
void		check_signal(int last_status);
void		heredoc_cntrlc(int signal);
void		dup_input(t_pipex *pipex);
void		dup_output(t_pipex *pipex);
void		childs_process(t_pipex *pipex, t_main *main, t_shell *shell, int i);
void		parent_process(t_pipex *pipex, t_main **main, int i);
void		cleanup_exit_process(int *pipe_fd, int prev_fd, int is_pipe,
				int code);
char		*command_founder(char **cmd_args, t_env *env);
int			check_exit(int status);

char		*env_strdup(const char *s1, char c);
char		**env_split(const char *s, char c);
char		*env_strjoin(char const *s1, char const *s2);

int			ft_strcmp(char *s1, char *s2);
char		*ft_strrchr(const char *s, int c);
int			permission_denied(char *dir, char *oldpwd,
				int free_oldpwd, t_shell *shell);
int			update_env_vars(t_shell *shell, char *oldpwd, int free_oldpwd);
int			ft_isdigit(int c);
int			is_valide_num(char *str);
int			ft_isalnum_unscore(char *str);
int			is_valide(char *str);
int			ft_atoi(const char *str, int *value);
void		ft_putstr_fd(char *s, int fd);
void		error(char *str1, char *str2, char *str3, char *str4);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		ft_putendl_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strdup(const char *s1, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_itoa(int n);
char		*ft_strndup(const char *s1, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t		env_strlen(const char *s, char c);
long long	ft_atoll(char *str, long long *num);

#endif
