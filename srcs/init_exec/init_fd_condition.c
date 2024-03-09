/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_condition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:11:18 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_input_fd_open_ready_for_read(t_node *node)
{
	return (node->input_fd > 0);
}

bool	is_append_out_followed_by_fd_token(t_lexer *lex_lst)
{
	return (lex_lst && lex_lst->next \
	&& lex_lst->token == APPEND_OUT \
	&& lex_lst->next->token == FD);
}

/**
 * Vérifie si le descripteur de fichier de sortie est ouvert et prêt à être
 * fermé.
 * 
 * @param node Le nœud contenant le descripteur de fichier de sortie à vérifier.
 * @return true si le descripteur de fichier de sortie est ouvert, false sinon.
 */
bool	is_output_fd_open_for_closing(t_node *node)
{
	return (node->output_fd > 0);
}
