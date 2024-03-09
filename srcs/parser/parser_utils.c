/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:12:06 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_strlen3_mini(char const *s)
{
	size_t	i;

	i = ZERO_INIT;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(t_data *data, char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*nouveau;

	if (s && start >= ft_strlen3_mini(s))
	{
		nouveau = malloc_track(data, sizeof(char));
		if (!nouveau)
			return (NULL);
		nouveau[0] = '\0';
		return (nouveau);
	}
	nouveau = \
	malloc_track(data, sizeof(char) * (len + sizeof('\0')));
	i = 0;
	if (!nouveau || !s)
		return (NULL);
	nouveau[len] = '\0';
	while (i < len && s[i + start])
	{
		nouveau[i] = s[i + start];
		i++;
	}
	nouveau[i] = '\0';
	return (nouveau);
}

int	is_white_space(char c)
{
	return (c == ' ' || (c > '\b' && c < SHIFT_OUT));
}

int	is_space(char *str, char c)
{
	int	i;

	i = ZERO_INIT;
	while (str[i])
	{
		if (str[i] == c)
		{
			ft_printf("found space");
			return (1);
		}
		i++;
	}
	return (0);
}
