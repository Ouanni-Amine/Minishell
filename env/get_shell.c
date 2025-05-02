/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:37:48 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/27 16:49:45 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

t_shell	*get_shell(t_shell *shell)
{
	static t_shell	*global_shell;

	if (shell)
		global_shell = shell;
	return (global_shell);
}
