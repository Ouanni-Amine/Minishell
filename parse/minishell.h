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


typedef enum e_token_type {
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    HEREDOC,
	VARIABLE
}   t_token_type;

typedef struct s_file
{
	char			*file;
	t_token_type	token;
	int				here_doc;//-1
	int				expand;//0 no 1 yes
	int				ambiguous;// 0 no 1 yes
	struct s_file	*next;
}	t_file;

typedef struct s_main
{
	char			**cmd;
	t_file			*redir;
	int				is_builtin;
	struct s_main	*next;
}	t_main;

typedef struct s_token {
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

typedef	struct	s_shell
{
	t_env			*env;
	int				last_status; // 258
	int				is_pipe;
	char			*pwd_emergcy;
	struct termios	term;
}	t_shell;

typedef struct s_pipex
{
	int		pipe_fd[2];
	int		prev_fd;
	int		pid;
	int		last_pid;
	int		nb_cmd;
	int		diff;
}	t_pipex;

void	lexer(char *str, t_token **head_lex);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen (char *str);
char	**ft_free_1(int word, char **s2);
void	print_tokens(t_token *head);
void	free_tokens(t_token *head);
char	*ft_make_space(char *str);
t_main	*ft_lstnew();
char	*parse_strdup(const char *s1);
void	ft_lstadd_back(t_main **lst, t_main *new);
void	print_main_debug(t_main *head);
void	free_main_list(t_main *head);
void	ft_parsing(t_token **head_lex, t_main **head);
void	ft_check_syntax_error(t_token *head_lex);
void	ft_exit_syntax_error();
int		ft_check_if_inside_cotes(char *str, size_t i);
void	ft_check_str(t_token **token);
char	*ft_skip_thinks(char *str);
// ********************************************************************************
int		ft_echo(char **cmd);
int		ft_cd(char **cmd, t_shell *shell);
int		ft_pwd(t_shell *shell);
int		ft_exit(char **cmd, t_shell *shell);
int		ft_env(char **cmd, t_env *env);
int		ft_unset(t_env **head, char **cmd);
void	*ft_malloc(size_t n);
void	ft_free(void *ptr, int flag);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int c);
void	env_add_back(t_env	**head, t_env *new);
int		is_valide_num(char *str);
t_env	*create_env_node(char *key, char *value, int i);
void	env_add_back(t_env	**head, t_env *new);
char	*get_env_value(t_env *env, char *key);
void	set_env_value(t_env **head, char *key, char *value, int i);
size_t	env_strlen(const char *s, char c);
char	*ft_strdup(const char *s1, char c);
char	*env_strdup(const char *s1, char c);
int		get_lenght(t_env *head);
char	**env_split(const char *s, char c);
int		ft_isalnum_unscore(char *str);
void	my_exit(int status);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	error(char *str1, char *str2, char *str3, char *str4);
char	*ft_strchr(const char *s, int c);
void	sort_export(t_env **env);
int		handle_redir(t_main *main);
int		handle_redir_heredoc(t_main *main, t_env *env);
int		heredoc_inputfd(t_file *current, t_env *env);
char	*command_founder(char **cmd_args, t_env *env);
int		run_single_cmd(t_main *main, t_shell *shell);
int		run_builtins(t_main *main, t_shell *shell);
void	extract_env(t_shell *shell, char **env);
int		is_valide(char *str);
int		ft_export(t_env **env, char **cmd);
char	**env_convertor(t_env *env);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str, int *value);
char	*ft_itoa(int n);
int		run_multi_cmd(t_main *main, t_shell *shell);
t_shell	*get_shell(t_shell *shell, int flag);
char	*env_strjoin(char const *s1, char const *s2);
void	my_clean(void);
void	heredoc_cleanup(t_main *main);
char	*ft_strtrim(char const *s1, char const *set);
long long	ft_atoll(char *str, long long *num);
void	cntrlc(int signal);
void	cntrlslash(int signal);
void	cntrlc_child(int signal);
void	set_last_status(int *last_status, int code);
void	heredoc_cntrlc(int signal);
void	dup_input(t_pipex *pipex);
void	dup_output(t_pipex *pipex);
void	childs_process(t_pipex *pipex, t_main *main, t_shell *shell, int i);
void	parent_process(t_pipex *pipex, t_main **main, int i);
int		parent_exit(t_pipex *pipex, t_main *main);
void	cleanup_exit_process(int *pipe_fd, int prev_fd, int is_pipe, int code);
void	cntrlc_specifique(int signal);
void	signal_part(t_main *main);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		here_doc_count(t_main *main);
#endif
