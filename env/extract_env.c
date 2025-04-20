/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:06:29 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/18 18:21:16 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

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
	}
	while (*env)
	{
		key = ft_strdup(*env, '=');
		if (ft_strcmp(key, "OLDPWD"))
		{
			val = ft_strdup(ft_strchr(*env, '=') + 1, '\0');
			env_add_back(head, create_env_node(key, val, 1));
		}
		env++;
	}
	env_add_back(head, create_env_node("OLDPWD", "", 0));
}
