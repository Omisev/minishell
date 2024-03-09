/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_search_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:27:20 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_and_expand_env_var_with_special_char(\
char *w, t_expand *exp, t_data *data, t_quote *state)
{
	int	i;
	int	env_var_char_idx;

	i = -1;
	env_var_char_idx = ZERO_INIT;
	if (w[1] == '?')
		return (append_curnt_error_code_to_expansion_struc(exp, data));
	i = 1;
	while (is_matching_env_var_name(w, data, i, env_var_char_idx))
	{
		env_var_char_idx++;
		i++;
	}
	if (is_word_end_or_special(w, i, state) \
	&& is_env_var_name_with_equal_sign(data, env_var_char_idx))
	{
		exp->var_env_match_found = 1;
		while (data->full_env_var_copy_gamma[data->\
		env_var_line_idx][++env_var_char_idx])
			exp->value_of_expanded_var_from_env[exp->\
			length_of_expanded_var_value++] = data->\
			full_env_var_copy_gamma[data->env_var_line_idx][env_var_char_idx];
		return (i);
	}
	return (i);
}

/**
 * @nom: handle_unfound_expansion_word
 * @breve_description: Traite le cas où un mot d'expansion n'est pas trouvé.
 */
int	handle_unfound_expansion_word(char *w, t_quote *state)
{
	int	indx;

	indx = 1;
	if (w[indx])
	{
		while ((is_not_end_of_string_or_dollar_sign(w[indx])))
		{
			if (is_special_syntax_character(w[indx], state))
				return (indx);
			indx++;
		}
	}
	return (indx);
}
