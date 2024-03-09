/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:48:38 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:48:39 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *text, ...);
int		length_of_number_for_string_conversion(long n);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr_base(int nbr, char *base);
int		ft_putnbr_base_neg(unsigned int nbr, char *base);
int		ft_pointeur(void *ptr, char *base);
int		ft_putnbr_base_hex(unsigned int nbr, char *base);
int		ft_len_nb_hexa(unsigned long n);
void	*ft_memset(void *s, int c, size_t n);

#endif
