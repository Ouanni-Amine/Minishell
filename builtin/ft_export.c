/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:02:42 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/19 17:54:09 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	ft_export_show2(t_env *node)
{
	if (strcmp(node->key, "_"))
	{
		if (node->is_active)
		{
			if (node->value && node->value[0])
				printf("declare -x %s=\"%s\"\n", node->key, node->value);
			else
				printf("declare -x %s=\"\"\n", node->key);
		}
		else
			printf("declare -x %s\n", node->key);
	}
}

void	ft_export_show(t_env **env)
{
	int		j;
	int		i;
	t_env	*node;

	i = 0;
	j = get_lenght(*env);
	sort_export(env);
	while (i < j)
	{
		node = *env;
		while (node)
		{
			if (node->rank == i)
			{
				ft_export_show2(node);
				break ;
			}
			node = node->next;
		}
		i++;
	}
}

void ft_export_concatenate(char *cmd, t_env **env)
{
	char	*key;
	char	*val;
	char	*add;

		key = ft_strdup(cmd, '+');
		if (!key[0] || !is_valide(key))
			error("export: `", cmd, "': not a valid identifier", NULL);
		else
		{
			val = ft_strdup(ft_strchr(cmd, '=') + 1, '\0');
			add = get_env_value(*env, key);
			if (add)
				val = ft_strjoin(add, val);
			set_env_value(env, key, val, 1);
		}
}

void ft_export_add(char *cmd, t_env **env)
{
	char	*key;
	char	*val;

	key = ft_strdup(cmd, '=');
	if (!key[0] || !is_valide(key))
		error("export: `", cmd, "': not a valid identifier", NULL);
	else
	{
		val = ft_strdup(ft_strchr(cmd, '=') + 1, '\0');
		set_env_value(env, key, val, 1);
	}
}

void	ft_export(t_env **env, char **cmd)
{
	int		i;
	char	*res;

	i = 1;
	if (!cmd[i])
		ft_export_show(env);
	while (cmd[i])
	{
		res = ft_strchr(cmd[i], '=');
		if (!res)
		{
			if (!is_valide(cmd[i]))
			error("export: `", cmd[i],"': not a valid identifier", NULL);
			else if(!get_env_value(*env, cmd[i]))
				set_env_value(env, cmd[i], "", 0);
		}
		else
		{
			if (*(res - 1) == '+')
				ft_export_concatenate(cmd[i], env);
			else
				ft_export_add(cmd[i], env);
		}
		i++;
	}
}
