/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:45:03 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/20 11:22:20 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

int 	handle_redir(t_main *main)
{
	int fd;
	t_file *check_redir = main->redir;
	while (check_redir)
	{
		if (check_redir->token == 5)
		{
			fd = heredoc_inputfd(check_redir->file);
			if (fd < 0)
				return (1);
			if (!check_redir->next)
				dup2(fd, STDIN_FILENO);
			close(fd);
		}
	check_redir = check_redir->next;
	}
	while(main->redir)
	{
	if (main->redir->token == 2)
	{
		fd = open(main->redir->file, O_RDONLY);
		if (fd < 0)
		{
			printf("%s: No such file or directory\n", main->redir->file);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (main->redir->token == 3)
	{
		fd = open(main->redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			printf("%s: No such file or directory\n", main->redir->file);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (main->redir->token == 4)
	{
		fd = open(main->redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			printf("%s: No such file or directory\n", main->redir->file);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	main->redir = main->redir->next;
	}
	return (0);
}
