/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:48:10 by aouanni           #+#    #+#             */
/*   Updated: 2025/04/19 13:48:22 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin.h"

int	fill_tempfile(int input_fd, char *limiter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
			break ;
		if (write(input_fd, line, ft_strlen(line, '\0')) < 0)
		{
			perror("pipex");
			return (-1);
		}
	}
	close (input_fd);
	return (1);
}

int	heredoc_inputfd(char *v)
{
	int		input_fd;
	char	*limiter;

	limiter = ft_strjoin(v, "\n");
	input_fd = open("temp.txt", O_WRONLY | O_CREAT| O_TRUNC, 0644);
	if (input_fd < 0)
	{
		perror("pipex");
		return (-1);
	}
	if (fill_tempfile(input_fd, limiter) == -1)
		return (-1);
	input_fd = open("temp.txt", O_RDONLY);
	if (input_fd < 0)
	{
		perror("pipex");
		return (-1);
	}
	unlink("temp.txt");
	return (input_fd);
}
