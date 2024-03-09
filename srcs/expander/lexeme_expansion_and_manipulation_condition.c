/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme_expansion_and_manipulation_condition        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:59:39 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_expansion_required_and_unquoted(t_expand *exp)
{
	return (exp->dollar_sign_present == 1
		&& exp->sing_or_doub_quote_in_env_expansion == 0);
}

bool	is_there_remaining_elements(int index, int total_length)
{
	return (index < total_length);
}

bool	is_single_quote_with_closed_double_quotes(char c, t_quote *state)
{
	return (c == '\'' && is_doubl_quote_closed(state));
}

bool	is_double_quote_with_closed_single_quotes(char c, t_quote *state)
{
	return (c == '"' && is_single_quote_closed(state));
}

bool	is_dollar_char_then_end_of_string(t_lexer *exp)
{
	return (exp->cmd_segment[0] == '$' && exp->cmd_segment[1] == '\0');
}
