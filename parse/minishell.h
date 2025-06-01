/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:37:42 by aouanni           #+#    #+#             */
/*   Updated: 2025/06/01 21:11:29 by aouanni          ###   ########.fr       */
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
} t_token_type;

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

typedef struct	s_norm
{
	size_t i;
	size_t j;
	size_t start;
	size_t len;
	size_t k;
	t_token *tmp;
	t_token *past;
	t_token *prev;
	t_token *next;
	t_main *current_main;
	t_file *file_head;
	size_t cmd_index;
	size_t cmd_count;
	t_token *current_token;
}	t_norm;

char **ft_split(char const *s, char c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
size_t ft_strlen(char *str);
void print_tokens(t_token *head);
char *ft_make_space(char *str);
t_main *ft_lstnew();
char *parse_strdup(const char *s1);
void ft_lstadd_back(t_main **lst, t_main *new);
void print_main_debug(t_main *head);
int ft_check_syntax_error(t_token *head_lex);
void ft_exit_syntax_error();
void ft_check_str(t_token **token);
char *ft_skip_thinks(char *str, int cool);
void ft_free(void *ptr, int flag);
void *ft_malloc(size_t n);
size_t ft_lstsize(t_token *lst);
void ft_check_str_variable(t_token **token);
void	lexer(char *str, t_token **head_lex);
size_t ft_strlen(char *str);
int ft_symbols(char c);
char *ft_get_the_true_str3(char *str);
char *ft_strdup_updated(const char *s1, char c);
char *ft_get_the_true_str2(char *str);
char *ft_check_hard_str(char *str);
void ft_check_val(t_token **token, t_env *env, t_shell *shell);
char *ft_add_val_in(char *val, t_env *env, t_shell *shell);
t_file *create_file_node(t_token *token, t_env *env, t_shell *shell);
void ft_parsing(t_token **head_lex, t_main **head, t_env *env, t_shell *shell);
void ft_append_in_file_struct(t_token **current_token, t_file **file_head, t_env *env, t_shell *shell);
int count_words2(const char *s, char sep);
char *ft_strtrim(char const *s1, char const *s2);
int ft_strstr_match(const char *haystack, const char *needle);
int ft_if_key_valid(char *val);
char *change_quotes(char *str);
void ft_make_org_var(t_token **head_lex);
int ft_symbols_max(char c);
// ********************************************************************************
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
void		prepare_signals(void);
void		change_handler(int code);
void		check_signal(void);
void		heredoc_cntrlc(int signal);
void		dup_input(t_pipex *pipex);
void		dup_output(t_pipex *pipex);
void		childs_process(t_pipex *pipex, t_main *main, t_shell *shell, int i);
void		parent_process(t_pipex *pipex, t_main **main, int i);
void		cleanup_exit_process(int *pipe_fd, int prev_fd, int is_pipe,
				int code);
char		*command_founder(char **cmd_args, t_env *env);
int		check_exit(int status);

char		*env_strdup(const char *s1, char c);
char		**env_split(const char *s, char c);
char		*env_strjoin(char const *s1, char const *s2);

int			ft_strcmp(char *s1, char *s2);
char		*ft_strrchr(const char *s, int c);
int			permission_denied(char *dir, char *oldpwd, int free_oldpwd, t_shell *shell);
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
