/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd_management_and_init_vars_condition        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:58:51 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_current_token_cmd_arg(t_lexer *lexer_lst)
{
	return (lexer_lst && lexer_lst->token == ARG);
}

bool	is_index_less_than_num_nodes(int index, int num_nodes)
{
	return (index < num_nodes);
}
