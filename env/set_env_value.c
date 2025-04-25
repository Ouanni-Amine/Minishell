/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:13:51 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/24 23:57:42 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

void	set_env_value(t_env **head, char *key, char *value, int i)
{
	t_env	*temp;

	temp = *head;
	if (!key || !value)
		return ;
	while (temp)
	{
		if (!ft_strcmp(key, temp->key))
		{
			free(temp->value);
			temp->value = env_strdup(value, '\0');
			if (!temp->value)
				my_exit(1);
			temp->is_active = i;
			return ;
		}
		temp = temp->next;
	}
	env_add_back(head, create_env_node(key, value, i));
}
