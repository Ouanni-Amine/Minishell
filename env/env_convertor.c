/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convertor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:07:58 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/10 13:08:29 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

char	**env_convertor(t_env *env)
{
	int		len;
	char	**res;
	int		i;
	char	*value;

	i = 0;
	len = get_lenght(env);
	res = ft_malloc((sizeof(char *) * (len + 1)));
	res[len] = NULL;
	while (i < len)
	{
		value = ft_strjoin(env->key, "=");
		value = ft_strjoin(value, env->value);
		res[i] = value;
		env = env->next;
		i++;
	}
	return (res);
}
