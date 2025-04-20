/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:07:11 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/18 21:07:44 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	sort_export(t_env **env)
{
	t_env	*current;
	t_env	*compare;

	current = *env;
	while (current)
	{
		current->rank = 0;
		compare = *env;
		while (compare)
		{
			if (ft_strcmp(compare->key, current->key) < 0)
				current->rank++;
			compare = compare->next;
		}
		current = current->next;
	}
}
