/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:37:48 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/10 11:19:48 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

t_shell	*get_shell(t_shell *shell, int flag)
{
	static t_shell	*global_shell;

	if (flag == 1)
		global_shell = shell;
	else if (flag == 0)
		global_shell = NULL;
	return (global_shell);
}
