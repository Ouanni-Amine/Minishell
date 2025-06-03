/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnaji-e <abnaji-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:36:02 by abnaji-e          #+#    #+#             */
/*   Updated: 2025/06/03 07:00:55 by abnaji-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_key(char *str)
{
	size_t	i;
	size_t	cool;

	i = 0;
	cool = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	while (str[i])
	{
		if (str[i] == '+')
		{
			cool++;
			i++;
		}
		else if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= '0' && str[i] <= '9'))
			i++;
		else if ((str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
			i++;
		else
			return (0);
	}
	if (cool > 1)
		return (0);
	return (1);
}

int	ft_if_key_valid(char *val)
{
	if (ft_check_key(ft_strdup_updated(val, '=')))
		return (1);
	return (0);
}

int	check_str(char *val)
{
	size_t	i;

	i = 0;
	while (val[i])
	{
		if (val[i] == '\"' || val[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_expand(char *val)
{
	if (check_str(val))
	{
		return (1);
	}
	return (0);
}

int	ft_check_content(char *val, int type, t_shell *shell)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (type == 6)
	{
		str = ft_add_val_in(val, shell);
		if (count_words2(str, ' ') != 1)
			return (1);
	}
	return (0);
}
