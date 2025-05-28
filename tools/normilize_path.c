/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normilize_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:37:19 by aouanni           #+#    #+#             */
/*   Updated: 2025/05/28 11:44:46 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/minishell.h"

char	*join_path(char *a, char *b)
{
	if (a[ft_strlen(a) - 1] == '/')
		return (ft_strjoin(a, b));
	else
		return (ft_strjoin(ft_strjoin(a, "/"), b));
}

char	*normilize_path2(char **res, int j)
{
	int		i;
	char	*final;

	i = 0;
	final = ft_strdup("/", '\0');
	while (i < j)
	{
		final = ft_strjoin(final, res[i]);
		if (i < j - 1)
			final = ft_strjoin(final, "/");
		i++;
	}
	return (final);
}

char	*normilize_path(char *combined)
{
	char	**str;
	int		i;
	char	**res;
	int		j;

	i = 0;
	j = 0;
	str = env_split(combined, '/');
	while (str[i])
		i++;
	res = ft_malloc(sizeof(char *) * (i + 1));
	res[i] = NULL;
	i = 0;
	while (str[i])
	{
		if (!ft_strcmp(str[i], ".."))
		{
			if (j > 0)
				j--;
		}
		else if (ft_strcmp(str[i], "." ) && str[i][0])
			res[j++] = str[i];
		i++;
	}
	return (normilize_path2(res, j));
}

int	permission_denied(char *dir, char *oldpwd, int free_oldpwd, t_shell *shell)
{
	char	*normilized_full;
	char	*normilized_short;

	if (errno == 13 && dir[0] != '/'
		&& ft_strnstr(dir, "..", ft_strlen(dir)))
	{
		normilized_full = normilize_path(join_path(oldpwd, dir));
		normilized_short = normilize_path(join_path(oldpwd, ".."));
		if (!access(normilized_short, X_OK) && chdir(normilized_full) != -1)
			return (update_env_vars(shell, oldpwd, free_oldpwd));
	}
	return (-1);
}
