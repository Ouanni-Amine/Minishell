/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:38:27 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/07 18:11:44 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	ft_env(char **cmd, t_env *env)
{
	if (cmd[1])
	{
		error("minishell: env: ", cmd[1], ": No such file or directory", NULL);
		return (127);
	}
	while (env)
	{
		if (env->value && env->is_active)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
