/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requirements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:36:22 by aouanni           #+#    #+#             */
/*   Updated: 2025/06/03 13:53:44 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valide_requirements(void)
{
	char	*res;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		ft_putstr_fd("minishell: minishell run only in a tty\n", 2);
		return (1);
	}
	res = getcwd(NULL, 0);
	if (!res)
	{
		ft_putstr_fd("minishell: minishell cannot run in orphan path\n", 2);
		return (1);
	}
	free(res);
	return (0);
}

void	prepare_requirements(t_shell *shell, char **env)
{
	char	*df_path;

	df_path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	tcgetattr(STDIN_FILENO, &shell->term);
	get_shell(shell, 1);
	extract_env(shell, env, df_path);
	rl_catch_signals = 0;
	prepare_signals();
}
