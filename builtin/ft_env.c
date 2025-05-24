/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:38:27 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/24 14:45:54 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	ft_env(char **cmd, t_env *env)
{
	char	*str;
	char	*res;

	str = NULL;
	res = NULL;
	if (cmd[1])
	{
		error("minishell: env: ", cmd[1], ": No such file or directory", NULL);
		return (127);
	}
	while (env)
	{
		if (env->value && env->is_active)
		{
			res = ft_strjoin(env->key, "=");
			res = ft_strjoin(res, env->value);
			res = ft_strjoin(res, "\n");
			str = ft_strjoin(str, res);
		}
		env = env->next;
	}
	if (str)
		printf("%s", str);
	return (0);
}
