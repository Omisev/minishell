/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:12:23 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	is_double_operator(const char *command, size_t pos)
{
	return ((command[pos] == '<' && command[pos + 1] == '<') || \
			(command[pos] == '<' && command[pos + 1] == '>') || \
			(command[pos] == '>' && command[pos + 1] == '<') || \
			(command[pos] == '>' && command[pos + 1] == '>'));
}

size_t	calculate_new_length(const char *command)
{
	size_t	new_len;
	size_t	i;

	i = 0;
	new_len = 0;
	while (command[i])
	{
		if (is_double_operator(command, i))
		{
			new_len += 4;
			i++;
		}
		else if (is_operator(command[i]))
			new_len += 3;
		else
			new_len++;
		i++;
	}
	return (new_len);
}

void	fill_command_with_spaces(const char *command, char *new_command, \
		t_quote *state, size_t i)
{
	size_t	j;

	j = 0;
	while (command[i])
	{
		update_quoting_state(command[i], state);
		if (is_double_operator(command, i) && (!state->doubl_quot_status && \
			!state->singl_quot_status))
		{
			new_command[j++] = ' ';
			new_command[j++] = command[i++];
			new_command[j++] = command[i++];
			new_command[j++] = ' ';
		}
		else if (is_operator(command[i]) && (!state->doubl_quot_status && \
				!state->singl_quot_status))
		{
			new_command[j++] = ' ';
			new_command[j++] = command[i++];
			new_command[j++] = ' ';
		}
		else
			new_command[j++] = command[i++];
	}
	new_command[j] = '\0';
}

char	*add_spaces_around_operators(t_data *data, const char *command)
{
	size_t	new_len;
	size_t	i;
	char	*new_command;
	t_quote	*state;

	state = malloc_track(data, sizeof(t_quote));
	if (!state)
		return (0);
	state->doubl_quot_status = 0;
	state->singl_quot_status = 0;
	new_len = calculate_new_length(command);
	new_command = malloc_track(data, new_len + 1);
	if (!new_command)
		return (NULL);
	i = 0;
	fill_command_with_spaces(command, new_command, state, i);
	return (new_command);
}
