/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_word_condition.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:11:28 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_next_word_existing_and_readable(t_lexer *lexer_lst)
{
	return (lexer_lst->next \
	&& lexer_lst->next->cmd_segment \
	&& !access(lexer_lst->next->cmd_segment, R_OK));
}

bool	is_next_word_missing(t_lexer *lexer_lst)
{
	return (!lexer_lst->next->cmd_segment);
}

bool	is_next_lexeme_word_existing(t_lexer *lex_lst)
{
	return (lex_lst->next && lex_lst->next->cmd_segment);
}
