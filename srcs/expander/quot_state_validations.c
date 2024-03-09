/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_state_validations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:59:55 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_single_quote_started(t_quote *state)
{
	return (state->singl_quot_start_status == SINGLE_QUOTE_STARTED);
}

int	is_single_quote_started_double_quote_closed(t_quote *state)
{
	return (is_single_quote_started(state) && is_doubl_quote_closed(state));
}

int	is_single_quote_open_and_started(t_quote *state)
{
	return (is_single_quote_open(state) && is_single_quote_started(state));
}
