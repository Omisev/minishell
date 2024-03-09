/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:26:23 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @fonction: reset_quoting_state
 * @brief: Réinitialise l'état des guillemets dans une structure 't_quote'.
 */
void	reset_quoting_state(t_quote *state)
{
	state->doubl_quot_status = ZERO_INIT;
	state->singl_quot_status = ZERO_INIT;
}

/**
 * @nom: length_of_number_for_string_conversion
 * @brief: Calcule la longueur d'un nombre lorsqu'il est représenté en tant que
 * chaîne de caractères.
 *
 * @description:
 * Détermine le nombre de chiffres nécessaires pour représenter un entier 'n'
 * sous forme de chaîne. Cette fonction est particulièrement utile pour allouer
 * la bonne quantité de mémoire lors de la conversion d'entiers en chaînes de
 * caractères, comme dans la fonction 'ft_itoa'.
 */
int	length_of_number_for_string_conversion(long n)
{
	int	length;

	length = ZERO_INIT;
	if (n == 0)
	{
		length = 1;
		return (length);
	}
	while (n != 0)
	{
		length++;
		n /= 10;
	}
	return (length);
}

/**
 * @nom: ft_is_neg
 * @brief: Traite les nombres négatifs pour la conversion en chaîne de 
 * caractères.
 *
 * @description:
 * Convertit un nombre négatif 'n' en une chaîne de caractères, en ajoutant un
 * signe moins au début de la chaîne. La fonction alloue de la mémoire pour
 * accueillir la représentation textuelle du nombre, y compris le signe moins.
 * Cette fonction est un complément à 'ft_itoa' pour gérer spécifiquement les
 * nombres négatifs.
 */
char	*convert_negative_int_to_string_with_tracking(\
t_data *data, char *res, long n, int length)
{
	n = n * (-1);
	res = \
	malloc_track(\
	data, sizeof(char) * length + sizeof('-') + sizeof('\0'));
	if (!res)
		return (NULL);
	res[0] = '-';
	res[length + FORWARD_OFFSET] = '\0';
	while (length >= 1)
	{
		res[length] = (n % 10) + '0';
		n /= 10;
		length--;
	}
	return (res);
}

/**
 * @nom: ft_itoa
 * @brief: Convertit un entier en une chaîne de caractères.
 *
 * @description:
 * Convertit un entier 'n' en une chaîne de caractères représentative. 
 * La fonction gère les valeurs négatives et alloue dynamiquement une nouvelle
 * chaîne pour contenir le résultat. Cette fonction est utile pour convertir
 * des nombres en chaînes pour l'affichage, la journalisation ou d'autres
 * formes de traitement textuel.
 */
char	*convert_int_to_string_with_tracking(t_data *data, int n)
{
	long	nb;
	int		index;
	char	*res;

	nb = (long)n;
	res = ZERO_INIT;
	index = length_of_number_for_string_conversion(nb);
	if (nb < 0)
	{
		res = \
		convert_negative_int_to_string_with_tracking(data, res, nb, index);
		return (res);
	}
	res = malloc_track(data, sizeof(char) * (index + sizeof('\0')));
	res[index] = '\0';
	if (!res)
		return (NULL);
	index--;
	while (index >= 0)
	{
		res[index] = (nb % 10) + '0';
		nb /= 10;
		index--;
	}
	return (res);
}

/**
 * @nom: is_decimal_digit
 * @brief: Vérifie si un caractère est un chiffre décimal.
 *
 * @description:
 *   La fonction 'is_decimal_digit' détermine si le caractère donné 'c' est un
 * chiffre décimal (0 à 9). Cette fonction est essentielle pour les opérations
 * de traitement de texte où il est nécessaire de distinguer les chiffres des
 * autres caractères.
 */
int	is_decimal_digit(char c)
{
	return (c >= '0' && c <= '9');
}
