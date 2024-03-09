/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_condition_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:11:14 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_current_token_pipe(t_lexer *lexer_lst)
{
	return (lexer_lst && lexer_lst->token == PIPE);
}

bool	is_current_token_not_pipe(t_lexer *lexer_lst)
{
	return (lexer_lst && lexer_lst->token != PIPE);
}
