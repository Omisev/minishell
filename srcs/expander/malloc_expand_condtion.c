/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_expand_condtion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:59:49 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_char_non_space_and_copyable(char current_char)
{
	return (current_char != '\0' && current_char != ' ');
}

bool	is_next_char_non_space(char *word, int index)
{
	return (word[index + 1] != ' ');
}

bool	is_next_char_present(char *word, int index)
{
	return (word[index + 1] != '\0');
}

bool	is_start_of_word(char *word, int index)
{
	return (word[index] != ' ' && (index == 0 || word[index - 1] == ' '));
}
