/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convertor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:07:58 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/18 18:19:17 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

char	**env_convertor(t_env *env)
{
	int		len;
	char	**res;
	int		i;
	char	*value;

	i = 0;
	len = get_lenght(env);
	res = ft_malloc((sizeof(char *) * len) + 1);
	res[len] = NULL;
	while (i < len)
	{
		value = ft_strjoin(env->key, "=");
		value = ft_strjoin(value, env->value);
		res[i] = ft_strdup(value, '\0');
		i++;
		env = env->next;
	}
	return (res);
}
