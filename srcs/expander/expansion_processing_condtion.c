/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_processing_condtion.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:59:20 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_current_char_dollar_sign(t_lexer *exp, int index)
{
	return (exp->cmd_segment[index] == '$');
}

bool	is_next_char_end_space_dash_or_special(\
t_lexer *expnd, t_quote *state, int index)
{
	char	next_char;

	next_char = expnd->cmd_segment[index + 1];
	return (is_next_char_end_or_special(&expnd->cmd_segment[index], state) \
	|| next_char == '\0' || next_char == ' ' || next_char == '-');
}
