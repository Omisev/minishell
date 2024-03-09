/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:52:41 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:52:44 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

char	*ft_strchr(char *str, int c)
{
	char	ch;
	int		index;

	ch = c;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == ch)
			return ((char *)(str + index));
		index++;
	}
	return (0);
}
