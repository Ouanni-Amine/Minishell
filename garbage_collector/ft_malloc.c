/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:23:52 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/17 17:51:09 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

void	ft_free(void *ptr, int flag)
{
	static void	*lst[INT_MAX];
	static int	i;
	int			j;

	if (flag)
	{
		j = 0;
		while (j < i && lst[j])
		{
			free(lst[j]);
			lst[j] = NULL;
			j++;
		}
		i = 0;
	}
	else
		lst[i++] = ptr;
}

void	my_clean(void)
{
	ft_free(NULL, 1);
}

void	my_exit(int status)
{
	t_shell	*shell;
	t_env	*env;
	t_env	*next;

	rl_clear_history();
	ft_free(NULL, 1);
	shell = get_shell(NULL, 2);
	env = shell->env;
	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
	if (shell->pwd_emergcy)
		free(shell->pwd_emergcy);
	free(shell);
	get_shell(NULL, 0);
	exit(status);
}

void	*ft_malloc(size_t n)
{
	void	*ptr;

	ptr = malloc(n);
	if (!ptr)
		my_exit(1);
	ft_free(ptr, 0);
	return (ptr);
}
