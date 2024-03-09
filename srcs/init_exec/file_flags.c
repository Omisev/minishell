/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:10:37 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	out_to_file_flags(void)
{
	return (O_CREAT | O_RDWR | O_TRUNC);
}

int	append_to_file_flags(void)
{
	return (O_CREAT | O_RDWR | O_APPEND);
}

int	heredoc_tmp_file_flags(void)
{
	return (O_CREAT | O_WRONLY | O_TRUNC);
}
