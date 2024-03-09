/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:52:25 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:52:27 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../../include/minishell.h"

int	ft_strlen3(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd_mini(char *s1, char *s2, int fd, t_data *data)
{
	char	*s;
	char	*final;

	if (s2)
	{
		s = ft_strjoin2_mini(s1, s2, data);
		final = ft_strjoin2_mini(s, "\n", data);
		write (fd, final, ft_strlen3(final));
		free (s);
		free (final);
	}
	else
	{
		write (fd, s1, ft_strlen3(s1));
		write (fd, "\n", 1);
	}
}
