/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management_and_expander_utils.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:31:36 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @fonction: update_quoting_state
 * @breve_description: Met à jour l'état des guillemets dans une analyse de
 * chaîne de caractères
 */
void	update_quoting_state(char c, t_quote *state)
{
	if (c == '\'')
	{
		if (is_single_quote_closed(state))
			state->singl_quot_status = SIMPL_QUOT_OPEN;
		else
		{
			state->singl_quot_start_status = SINGLE_QUOTE_NOT_STARTED;
			state->singl_quot_status = SIMPL_QUOT_CLOS;
		}
	}
	else if (c == '"')
	{
		if (is_doubl_quote_closed(state))
			state->doubl_quot_status = DOUBL_QUOT_OPEN;
		else
			state->doubl_quot_status = DOUBL_QUOT_CLOS;
	}
	if (is_only_single_quote_on(state))
		state->singl_quot_start_status = SINGLE_QUOTE_STARTED;
}

/**
 * @fonction: is_char_cmd_separator
 * @breve_description: Vérifie si un caractère est un séparateur de mot.
 */
int	is_char_cmd_separator(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ')
		return (IS_SEPARATOR);
	return (NOT_SEPARATOR);
}

bool	is_cmd_separator_and_quotes_off(char c, t_quote *state)
{
	return (is_char_cmd_separator(c) && is_both_quotes_off(state));
}

/**
 * @fonction: is_end_of_command_word
 * @breve_description: Détermine si le caractère actuel marque la fin d'un mot
 * dans une chaîne de commande.
 */
int	is_end_of_command_word(char *cmd, int i, t_quote *state)
{
	if (is_cmd_separator_and_quotes_off(cmd[i], state))
		return (TRUE);
	return (FALSE);
}

/**
 * @fonction: count_string_array_elements
 * @breve_description: Calcule la longueur d'un tableau de chaînes de
 * caractères.
 */
int	count_string_array_elements(char **arr)
{
	int	index;

	index = ZERO_INIT;
	while (arr[index])
		index++;
	return (index);
}
