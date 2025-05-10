/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:14:45 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/06 12:14:01 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

int	redirect_input(t_file *current)
{
	int	fd;
	int	flag;

	if (current->token == 2)
	{
		fd = open(current->file, O_RDONLY);
		if (fd < 0)
		{
			error("minishell: ", current->file, ": ", strerror(errno));
			return (1);
		}
	}
	else
		fd = current->here_doc;
	if (dup2(fd, 0) == -1)
	{
		perror("minishell: dup2");
		return (close(fd), 1);
	}
	return (close(fd), 0);
}

int	redirect_output(t_file *current)
{
	int	fd;
	int	flag;

	flag = O_CREAT | O_WRONLY;
	if (current->token == 3)
		flag |= O_TRUNC;
	else
		flag |= O_APPEND;
	fd = open(current->file, flag, 0644);
	if (fd < 0)
	{
		error("minishell: ", current->file, ": ", strerror(errno));
		return (1);
	}
	if (dup2(fd, 1) == -1)
	{
		perror("minishell: dup2");
		return (close(fd), 1);
	}
	return (close(fd), 0);
}

int	handle_redir(t_main *main)
{
	int		fd;
	t_file	*current;

	current = main->redir;
	while (current)
	{
		// if (current->ambiguous)
		// {
		// 	error("minishell: ", current->file, ": ambiguous redirect", 0);
		// 	return (1);
		// }
		if (current->token == 2 || current->token == 5)
		{
			if (redirect_input(current))
				return (1);
		}
		else if (current->token == 3 || current->token == 4)
		{
			if (redirect_output(current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
