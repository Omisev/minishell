/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_expansion_and_manipulation_utils.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:27:36 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @function: reset_quote_states
 * @brief: Réinitialise les états des guillemets simples et doubles.
 */
void	reset_quote_states(t_quote *st)
{
	st->singl_quot_status = ZERO_INIT;
	st->doubl_quot_status = ZERO_INIT;
}

/**
 * @function: initialize_expansion_parameters
 * @brief: Initialise les paramètres nécessaires pour l'expansion des lexèmes.
 */
void	initialize_expansion_parameters(\
t_expand *exp, t_data *data, t_lexer **expnd, t_quote *st)
{
	exp->length_of_expanded_var_value = ZERO_INIT;
	data->utils->g_signal_in_char_format = \
	convert_int_to_string_with_tracking(data, g_globi);
	exp->value_of_expanded_var_from_env = \
	allocate_memory_for_expanded_word(expnd, st, data->\
	full_env_var_copy_gamma, data);
}
