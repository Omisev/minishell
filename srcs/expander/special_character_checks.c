/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_character_checks.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:32:24 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_special_syntax_character(char c, t_quote *st)
{
	(void)st;
	if (c)
	{
		if (c == ':' || c == '=' || c == '%' || c == '^' || c == '+' || c == '~'
			|| c == '/' || c == ' '
			|| ((c == '"' || c == '\''))
			|| c == ']' || c == '@' || c == ',')
			return (1);
	}
	return (0);
}

/**
 * @nom: is_dollar_or_doubl_or_singl_quote
 * @brief: Vérifie la présence de caractères spéciaux dans une chaîne.
 */
int	is_dollar_or_doubl_or_singl_quote(char *word)
{
	int	index;

	index = ZERO_INIT;
	while (word[index])
	{
		if (word[index] == '$' || word[index] == '"' || word [index] == '\'')
			return (CHAR_IS_SPECIAL);
		index++;
	}
	return (CHAR_IS_NOT_SPECIAL);
}

/**
 * @nom: is_dollar_at_end
 * @brief: Vérifie si un symbole dollar se trouve à la fin d'une chaîne de
 * caractères.
 */
int	is_dollar_at_end(char *str)
{
	int	index;

	index = ZERO_INIT;
	while (str[index])
		index++;
	if (str[--index] == '$')
		return (CHAR_IS_DOLLAR);
	return (CHAR_IS_NOT_DOLLAR);
}
