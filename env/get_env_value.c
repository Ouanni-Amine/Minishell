/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:13:13 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/18 18:13:22 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
