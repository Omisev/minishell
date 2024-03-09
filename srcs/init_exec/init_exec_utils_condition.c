/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_utils_condition.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:10:58 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_first_input_redirection_error(t_node *node)
{
	return (!node->is_input_redirection_failed);
}

bool	is_current_lexer_token_cmd(t_lexer *current_lexer)
{
	return (current_lexer->token == CMD);
}

bool	is_pipe_or_end_of_lexer_linked_list(t_lexer *element)
{
	return (element->token == PIPE || element->next == NULL);
}
