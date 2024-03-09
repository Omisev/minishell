/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:29:27 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @nom: malloc_copy_string_excluding_inactive_quotes
 * @breve_description: Alloue de la mémoire pour une nouvelle chaîne sans
 * guillemets.
 */
char	*malloc_copy_string_excluding_inactive_quotes(\
int len, char *old, t_quote *state, t_data *data)
{
	char	*nw;

	nw = malloc_track(data, sizeof(char) * (len + sizeof('\0')));
	if (!nw)
		return (NULL);
	return (copy_string_excluding_quotes(old, nw, state));
}

/**
 * @nom: create_cleaned_str_excluding_inactive_quots
 * @breve_description: Supprime les guillemets d'une chaîne de caractères en
 * tenant compte de l'état des guillemets.
 */
char	*create_cleaned_str_excluding_inactive_quots(\
char *old, t_quote *state, t_data *data)
{
	int		i;
	int		len;

	i = -1;
	len = ZERO_INIT;
	state->singl_quot_status = 0;
	state->doubl_quot_status = 0;
	while (old[++i])
	{
		update_quoting_state(old[i], state);
		if (is_both_quotes_on(state))
			len++;
		if (is_double_quote_with_single_quote_closed(old[i], state))
			continue ;
		if (is_single_quote_with_double_quote_closed(old[i], state))
			continue ;
		len++;
	}
	return (\
	malloc_copy_string_excluding_inactive_quotes(len, old, state, data));
}

/**
 * @nom: is_start_word_considering_quotes
 * @breve_description: Détermine si le caractère à l'indice spécifié marque le
 * début d'un mot.
 */
int	is_start_word_considering_quotes(char *word, int index, t_quote *state)
{
	if (is_start_of_word(word, index))
	{
		if (is_quote_char_with_closed_state(word[index], state))
		{
			if (is_next_char_present(word, index))
				if (is_next_char_non_space(word, index))
					return (1);
		}
		else
			return (1);
	}
	return (0);
}

/**
 * @nom: copy_alloc_memory_excluding_inactive_quot
 * @breve_description: Copie un mot depuis une chaîne en tenant compte de
 * l'état des guillemets.
 */
char	*copy_alloc_memory_excluding_inactive_quot(\
char *word, t_quote *state, char *str)
{
	int		i;
	int		j;

	i = ZERO_INIT;
	j = ZERO_INIT;
	while (is_char_non_space_and_copyable(word[i]))
	{
		if (is_quote_not_part_of_string(word[i], state))
			i++;
		else
		{
			str[j++] = word[i];
			i++;
		}
	}
	str[j] = '\0';
	return (str);
}

/**
 * @nom: alloc_copy_word_excluding_quot_with_tracking
 *
 * @description: Alloue de la mémoire pour une copie d'un mot, en tenant
 * compte des états de citation et de double citation.
 */
char	*alloc_copy_word_excluding_quot_with_tracking(\
char *word, t_quote *state, t_data *data)
{
	char	*str;
	int		i;
	int		j;

	i = ZERO_INIT;
	j = ZERO_INIT;
	while (is_char_non_space_and_copyable(word[i]))
	{
		if (is_quote_not_part_of_string(word[i], state))
			i++;
		else
		{
			i++;
			j++;
		}
	}
	str = malloc_track(data, sizeof(char) * (j + sizeof('\0')));
	if (!str)
		return (NULL);
	return (copy_alloc_memory_excluding_inactive_quot(word, state, str));
}
