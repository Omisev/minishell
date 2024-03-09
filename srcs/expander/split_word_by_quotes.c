/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_by_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:32:46 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @nom: count_subwords_with_quote_states
 *
 * @description: Calcule le nombre de sous-mots dans un mot, en tenant compte
 *               des états de citation et de double citation.
 */
int	count_subwords_with_quote_states(char *word, t_quote *state)
{
	int		index;
	int		j;

	index = ZERO_INIT;
	j = ZERO_INIT;
	state->doubl_quot_status = ZERO_INIT;
	state->singl_quot_status = ZERO_INIT;
	while (word[index])
	{
		update_quoting_state(word[index], state);
		if (is_start_word_considering_quotes(word, index, state))
			j++;
		index++;
	}
	return (j);
}

/**
 * @nom: split_word_by_quotes
 *
 * @description:
 * Sépare un mot en plusieurs sous-mots en fonction des citations et des
 * doubles citations.
 */
char	**split_word_by_quotes(t_data *data, char *word, t_quote *state)
{
	int		index;
	int		j;
	char	**arr;

	arr = \
	malloc_track(\
	data, sizeof(char *) * (count_subwords_with_quote_states(\
	word, state) + sizeof('\0')));
	if (!arr)
		return (NULL);
	index = ZERO_INIT;
	j = ZERO_INIT;
	state->doubl_quot_status = ZERO_INIT;
	state->singl_quot_status = ZERO_INIT;
	while (word[index])
	{
		update_quoting_state(word[index], state);
		if (is_start_word_considering_quotes(word, index, state))
			arr[j++] = \
			alloc_copy_word_excluding_quot_with_tracking(\
			&word[index], state, data);
		index++;
	}
	arr[j] = NULL;
	return (arr);
}
