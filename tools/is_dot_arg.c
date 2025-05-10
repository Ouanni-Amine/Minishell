/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dot_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:27:25 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/09 15:27:38 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	is_dot_arg(char *arg)
{
	if (!arg)
		return (0);
	if (strcmp(arg, "..") == 0)
		return (1);
	if (strcmp(arg, ".") == 0)
		return (1);
	if (strcmp(arg, "../") == 0)
		return (1);
	if (strcmp(arg, "./") == 0)
		return (1);
	return (0);
}
