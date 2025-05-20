/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:02:42 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/18 20:25:31 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	ft_export_show2(t_env *node)
{
	if (!strcmp(node->key, "_"))
		return ;
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

void	ft_export_show(t_env **env)
{
	int		len;
	int		i;
	t_env	*node;

	i = 0;
	len = get_lenght(*env);
	sort_export(env);
	while (i < len)
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

void	ft_export_func(char *cmd, t_env **env, char *res, int *status)
{
	char	*key;
	char	*add;

	if (res > cmd && *(res - 1) == '+')
		key = ft_strdup(cmd, '+');
	else
		key = ft_strdup(cmd, '=');
	if (!key[0] || !is_valide(key) || (res - cmd >= 2 && *(res - 2) == '+'))
	{
		error("minishell: export: `", cmd, "': not a valid identifier", NULL);
		*status = 1;
	}
	if (res > cmd && *(res - 1) == '+')
	{
		add = ft_strjoin(get_env_value(*env, key), ft_strchr(cmd, '=') + 1);
		set_env_value(env, key, add, 1);
	}
	else
		set_env_value(env, key, ft_strchr(cmd, '=') + 1, 1);
}

int	ft_export(t_env **env, char **cmd)
{
	int		i;
	int		status;

	status = 0;
	i = 1;
	if (!cmd[i])
		ft_export_show(env);
	while (cmd[i])
	{
		if (!ft_strchr(cmd[i], '='))
		{
			if (!is_valide(cmd[i]) || cmd[i][0] == '\0')
			{
				error("minishell: export: `", cmd[i],
					"': not a valid identifier", NULL);
				status = 1;
			}
			else if (!get_env_value(*env, cmd[i]))
				set_env_value(env, cmd[i], "", 0);
		}
		else
			ft_export_func(cmd[i], env, ft_strchr(cmd[i], '='), &status);
		i++;
	}
	return (status);
}
