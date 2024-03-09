/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion_length_condtion.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:59:07 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_char_matching_env_var(\
char *word, int word_index, char *env_var, int env_var_index)
{
	return (word[word_index] == env_var[env_var_index]);
}

bool	increment_length_if_env_var_not_ended(\
char *env_var, int *y, int *length)
{
	if (env_var[*y])
	{
		(*length)++;
		(*y)++;
		return (true);
	}
	return (false);
}
