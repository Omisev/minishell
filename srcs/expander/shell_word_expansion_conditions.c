/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_word_expansion_conditions.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:00:07 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_expansion_not_required_and_quoted(t_expand *exp)
{
	return (exp->dollar_sign_present == NO_EXPAND \
	&& exp->sing_or_doub_quote_in_env_expansion == QUOTED);
}

bool	is_singl_or_doubl_quote(char character)
{
	return (character == '"' || character == '\'');
}

bool	is_dollar_sign(char character)
{
	return (character == '$');
}

bool	is_the_token_a_delimiter(t_token token)
{
	return (token == DELIMITER);
}

bool	is_word_non_empty(const char *word)
{
	return (word && *word);
}
