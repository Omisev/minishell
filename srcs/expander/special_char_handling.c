/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:10:13 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_next_char_end_or_special(char *word, t_quote *state)
{
	return (word[FORWARD_OFFSET] == '\0' \
	|| is_special_syntax_character(word[FORWARD_OFFSET], state));
}

int	is_next_char_decimal_digit(char *word)
{
	return (word[FORWARD_OFFSET] && is_decimal_digit(word[FORWARD_OFFSET]));
}

int	is_special_char_found_with_state_not_found(\
t_lexer *exp, t_quote *state, int index)
{
	return (state->var_env_match_confirmed == 0 && exp->cmd_segment[index] \
	&& is_special_syntax_character(exp->cmd_segment[index], state));
}

int	is_next_char_question_mark(t_lexer *exp, int index)
{
	return (exp->cmd_segment[index + FORWARD_OFFSET] \
	&& exp->cmd_segment[index + FORWARD_OFFSET] == '?');
}
