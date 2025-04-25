/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:11:24 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/24 22:12:06 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

t_env	*create_env_node(char *key, char *value, int i)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		my_exit(1);
	node->key = env_strdup(key, '\0');
	if (!node->key)
		my_exit(1);
	node->value = env_strdup(value, '\0');
	if (!node->value)
		my_exit(1);
	node->is_active = i;
	node->next = NULL;
	return (node);
}
