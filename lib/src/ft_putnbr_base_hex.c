/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:52:02 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:52:06 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <unistd.h>
#include <stdio.h>

static int	ft_strlenbase(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

int	ft_putnbr_base_hex(unsigned int nbr, char *base)
{
	long	nbr2;
	int		count;

	nbr2 = nbr;
	count = ft_len_nb_hexa(nbr2);
	if (nbr2 < 0)
	{
		ft_putchar('-');
		nbr2 = nbr2 * (-1);
		count++;
	}
	if (nbr2 >= ft_strlenbase(base))
		ft_putnbr_base((nbr2 / ft_strlenbase(base)), base);
	ft_putchar(base[(nbr2) % ft_strlenbase(base)]);
	return (count);
}
