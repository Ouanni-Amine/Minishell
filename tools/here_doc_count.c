/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:59:15 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/21 18:20:26 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	here_doc_count(t_main *main)
{
	t_file	*current;
	int		count;

	count = 0;
	while (main)
	{
		current = main->redir;
		while (current)
		{
			if (count >= 16)
				return (0);
			if (current->token == 5)
				count++;
			current = current->next;
		}
		main = main->next;
	}
	return (1);
}
