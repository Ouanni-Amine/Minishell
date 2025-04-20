/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:11:24 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/18 18:11:34 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

t_env	*create_env_node(char *key, char *value, int i)
{
	t_env	*node;

	node = ft_malloc(sizeof(t_env));
	node->key = ft_strdup(key, '\0');
	node->value = ft_strdup(value, '\0');
	node->is_active = i;
	node->next = NULL;
	return (node);
}
