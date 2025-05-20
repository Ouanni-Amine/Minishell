/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:29 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/19 13:55:44 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	all_nums(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	shell_num(char *str)
{
	long long		num;
	int				res;
	int				value;
	unsigned int	overf;

	res = ft_atoll(str, &num);
	if (!res && (num == LLONG_MAX || num == LLONG_MIN))
		return (1);
	if (num < INT_MIN || num > INT_MAX)
	{
		overf = (unsigned int)num;
		value = overf +1;
	}
	else
		value = (int)num +1;
	if (value < 0)
		value = 0;
	else if (value > 1000)
		value = 1;
	return (value);
}

void	shellvl(char *key, char *env, t_env **head)
{
	char	*val;
	int		res;

	val = env_strdup(ft_strchr(env, '=') + 1, '\0');
	if (val[0] && all_nums(val))
	{
		res = shell_num(val);
		if (res == 1000)
			env_add_back(head, create_env_node(key, "", 1));
		else
			env_add_back(head, create_env_node(key, ft_itoa(res), 1));
	}
	else
		env_add_back(head, create_env_node(key, "1", 1));
	free(val);
}

void	env_inherited(t_env	**head, char **env, char *key, char *val)
{
	while (*env)
	{
		key = env_strdup(*env, '=');
		if (!key)
			my_exit(1);
		if (ft_strcmp(key, "OLDPWD") && ft_strcmp(key, "SHLVL"))
		{
			val = env_strdup(ft_strchr(*env, '=') + 1, '\0');
			if (!val)
			{
				free(key);
				my_exit(1);
			}
			env_add_back(head, create_env_node(key, val, 1));
			free(val);
		}
		if (!ft_strcmp(key, "SHLVL"))
		{
			shellvl(key, *env, head);
		}
		free(key);
		env++;
	}
}

void	extract_env(t_env **head, char **env)
{
	char	*dir;
	char	*key;
	char	*val;

	if (!*env)
	{
		dir = getcwd(NULL, 0);
		env_add_back(head, create_env_node("PWD", dir, 1));
		env_add_back(head, create_env_node("SHLVL", "1", 1));
		env_add_back(head, create_env_node("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 1));
		free(dir);
	}
	else
		env_inherited(head, env, key, val);
	env_add_back(head, create_env_node("OLDPWD", "", 0));
}
