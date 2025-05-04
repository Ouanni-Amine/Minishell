/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_last_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:26:54 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/02 19:30:46 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	set_last_status(int *last_status, int code)
{
	static int *status;

	if (last_status)
		status = last_status;
	else
		*status = code;
}
