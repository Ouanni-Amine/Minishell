/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:23:17 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/20 12:06:14 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <readline/readline.h>
#include "pipex/GNL/get_next_line.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
}	t_token_type;

typedef struct s_file {
	char			*file;
	t_token_type	token;
	struct s_file	*next;
}	t_file;

typedef struct s_main {
	char			**cmd;
	t_file			*redir;
	int				is_builtin;
	struct s_main	*next;
}	t_main;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_active;
	int				rank;
	struct s_env	*next;
}	t_env;

void	ft_echo(char **cmd);
void	ft_cd(char **cmd, t_env **env);
void	ft_pwd(void);
void	ft_exit(char **cmd, int last_cmd_status);
void	ft_env(char **cmd, t_env *env);
void	ft_unset(t_env **head, char **cmd);
void	*ft_malloc(size_t n);
void    ft_free(void *ptr, int flag);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int c);
void	env_add_back(t_env	**head, t_env *new);
int		is_valide_num(char *str);
t_env	*create_env_node(char *key, char *value, int i);
void	env_add_back(t_env	**head, t_env *new);
char	*get_env_value(t_env *env, char *key);
void	set_env_value(t_env **head, char *key, char *value, int i);
size_t	ft_strlen(const char *s, char c);
char	*ft_strdup(const char *s1, char c);
int		get_lenght(t_env *head);
char	**ft_split(const char *s, char c);
int		ft_isalnum_unscore(char *str);
void    my_exit(void);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	error(char *str1, char *str2, char *str3, char *str4);
char	*ft_strchr(const char *s, int c);
void	sort_export(t_env **env);
int 	handle_redir(t_main *main);
int		heredoc_inputfd(char *v);
char	*command_founder(t_env *env, char **cmd_args);
int		run_single_cmd(t_main *main, t_env **env);
void	run_builtins(t_main *main, t_env **env);
void	extract_env(t_env **head, char **env);
int		is_valide(char *str);
void	ft_export(t_env **env, char **cmd);
char	**env_convertor(t_env *env);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif
