/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singular_quote_status_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:10:07 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_single_quote_open(t_quote *state)
{
	return (state->singl_quot_status == SIMPL_QUOT_OPEN);
}

int	is_single_quote_closed(t_quote *state)
{
	return (state->singl_quot_status == SIMPL_QUOT_CLOS);
}

int	is_doubl_quote_open(t_quote *state)
{
	return (state->doubl_quot_status == DOUBL_QUOT_OPEN);
}

int	is_doubl_quote_closed(t_quote *state)
{
	return (state->doubl_quot_status == DOUBL_QUOT_CLOS);
}
