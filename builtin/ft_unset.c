/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:09:06 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/10 10:57:02 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	ft_unset2(t_env *current, t_env *prev, char *cmd, t_env **head)
{
	while (current)
	{
		if (!strcmp(current->key, cmd))
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_env **head, char **cmd)
{
	int		i;
	t_env	*current;
	t_env	*prev;
	int		status;

	i = 1;
	status = 0;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		current = *head;
		prev = NULL;
		if (ft_isdigit(cmd[i][0]) || (!ft_isalnum_unscore(cmd[i])) ||
			!cmd[i][0])
		{
			error("minishell: unset: `", cmd[i], "': not a valid identifier",
				NULL);
			status = 1;
		}
		ft_unset2(current, prev, cmd[i], head);
		i++;
	}
	return (0);
}
