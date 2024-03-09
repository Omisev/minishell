/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion_length.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:25:22 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @nom: get_env_var_expansion_length
 * @brief: Compare un mot avec une variable d'environnement et calcule la
 * longueur d'expansion.
 *
 * @description:
 * Cette fonction compare chaque caractère d'un mot donné avec une variable
 * d'environnement spécifiée et calcule la longueur supplémentaire nécessaire
 * pour l'expansion en cas de correspondance. Elle s'assure que le mot
 * correspond exactement à la variable avant le signe '='.
 */
int	get_env_var_expansion_length(\
char *word, int *length, char *env_var, t_quote *state)
{
	int			i;
	int			y;

	i = ZERO_INIT;
	y = ZERO_INIT;
	while (word[i++] && env_var[y] \
	&& env_var[y] != '=' \
	&& word[i] == env_var[y])
		y++;
	if ((word[i] == '\0' \
	|| is_special_syntax_character(\
	word[i], state) || word[i] == '$') && env_var[y]
		&& y != 0 && env_var[y] == '=')
	{
		state->var_env_match_confirmed = 1;
		while (env_var[++y])
			(*length)++;
		return (i);
	}
	return (i);
}

/**
 * @nom: calculate_length_until_single_quote
 * @brief: Calcule la longueur d'expansion pour un mot dans des guillemets
 * simples.
 *
 * @description:
 * Parcourt un mot pour calculer sa longueur jusqu'à la prochaine occurrence
 * d'un guillemet simple, en supposant que le mot commence à l'intérieur de
 * guillemets simples. Cette fonction est utile pour traiter des chaînes entre
 * guillemets simples dans le contexte d'expansion de variables ou de
 * traitement de chaînes.
 */
int	calculate_length_until_single_quote(char *word, int *length)
{
	int		index;

	index = ZERO_INIT;
	while (word[index] && word[index] != '\'')
	{
		(*length)++;
		index++;
	}
	return (index);
}

int	process_env_var_expansion_if_match(\
char *word, char **env_var, t_quote *state, int *length)
{
	int	word_index;

	word_index = 1;
	if (is_char_matching_env_var(word, word_index, *env_var, 0))
	{
		word_index = get_env_var_expansion_length(\
		word, length, *env_var, state);
	}
	return (word_index);
}

int	calculate_length_for_env_expansion(\
char *word, char **env_var, t_quote *state, int *length)
{
	int	env_var_index;
	int	word_index;

	env_var_index = ZERO_INIT;
	state->var_env_match_confirmed = ZERO_INIT;
	if (is_only_single_quote_on(state))
		return (calculate_length_until_single_quote(word, length));
	else
	{
		while (env_var[env_var_index])
		{
			word_index = process_env_var_expansion_if_match(\
			word, &env_var[env_var_index], state, length);
			if (state->var_env_match_confirmed == 1)
				return (word_index);
			env_var_index++;
		}
	}
	return (word_index);
}

/**
 * @nom: calculate_expanded_env_var_length
 * @brief: Calcule la longueur d'expansion pour un mot donné en fonction des
 * variables d'environnement.
 *
 * @description:
 * Évalue un mot et ses correspondances potentielles dans les variables
 * d'environnement pour déterminer la longueur totale de la chaîne après
 * expansion. Cette fonction prend en compte les guillemets et les variables
 * d'environnement pour ajuster la longueur d'expansion.
 */
int	calculate_expanded_env_var_length(\
char *word, char **env_var, t_quote *state, int *length)
{
	state->var_env_match_confirmed = ZERO_INIT;
	if (is_only_single_quote_on(state))
		return (calculate_length_until_single_quote(word, length));
	else
	{
		return (calculate_length_for_env_expansion(\
		word, env_var, state, length));
	}
}
