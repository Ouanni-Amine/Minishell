/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:29 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/23 12:35:02 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

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

void	shellvl(char *key, char *env, t_env **head)
{
	char	*val;
	int		res;
	int		safe;

	val =  ft_strdup(ft_strchr(env, '=') + 1, '\0');;
	if (val[0])
	{
		if (all_nums(val))
		{
			safe = ft_atoi(val, &res);
			if (safe == 1 && res < 0)
				env_add_back(head, create_env_node(key, "0", 1));
			else if (safe == 1 && res < 999)
			{
				env_add_back(head, create_env_node(key, ft_itoa(res + 1), 1));
			}
			else if (safe == 1 && res == 999)
				env_add_back(head, create_env_node(key, "", 1));
			else
				env_add_back(head, create_env_node(key, "1", 1));
		}
	}
	else
		env_add_back(head, create_env_node(key, "1", 1));
}

void	extract_env(t_env **head, char **env)
{
	char	*key;
	char	*val;

	if (!*env)
	{
		env_add_back(head, create_env_node("PWD", getcwd(NULL, 0), 1));
		env_add_back(head, create_env_node("SHLVL", "1", 1));
		env_add_back(head, create_env_node("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 1));
		env_add_back(head, create_env_node("_", "./minishell", 1));
	}
	while (*env)
	{
		key = ft_strdup(*env, '=');
		if (ft_strcmp(key, "OLDPWD") && ft_strcmp(key, "SHLVL"))
		{
			val = ft_strdup(ft_strchr(*env, '=') + 1, '\0');
			env_add_back(head, create_env_node(key, val, 1));
		}
		if (!ft_strcmp(key, "SHLVL"))
			shellvl(key, *env, head);
		env++;
	}
	env_add_back(head, create_env_node("OLDPWD", "", 0));
}

