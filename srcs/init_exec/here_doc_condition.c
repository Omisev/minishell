/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_condition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:10:49 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_heredoc_delimiter_matched(char *delimiter, char *line)
{
	return (!ft_strncmp(delimiter, line, strlen2(delimiter)) \
	&& (strlen2(delimiter) == strlen2(line)));
}

bool	is_heredoc_ended_by_signal(t_data *data)
{
	return (!data->utils->heredoc_input_buffer \
	&& data->utils->heredoc_ctrl_c_uninterrupted);
}

bool	is_heredoc_interrupted_for_stdin_restore(t_data *data)
{
	return (!data->utils->heredoc_ctrl_c_uninterrupted);
}

bool	is_heredoc_file_opening_failed(int file_descriptor)
{
	return (file_descriptor < 0);
}

bool	is_valid_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
