/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:09:06 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/19 17:40:54 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

int	ft_isalnum_unscore(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90)
		|| (str[i] >= 97 && str[i] <= 122) || str[i] == 95)
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

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
			break ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_unset(t_env **head, char **cmd)
{
	int		i;
	t_env	*current;
	t_env	*prev;

	i = 1;
	if (!cmd[1])
		return ;
	while (cmd[i])
	{
		current = *head;
		prev = NULL;
		if (ft_isdigit(cmd[i][0]) || (!ft_isalnum_unscore(cmd[i])))
			error("minishell: unset: `", cmd[i], "': not a valid identifier", NULL);
		ft_unset2(current, prev, cmd[i], head);
		i++;
	}
}
