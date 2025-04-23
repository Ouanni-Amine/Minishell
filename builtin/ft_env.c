/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:38:27 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/20 16:54:22 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

int	ft_env(char **cmd, t_env *env)
{
	if (cmd[1])
	{
		error("env: ", cmd[1], ": No such file or directory", NULL);
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
