/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoure <lgoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/25 14:33:01 by lgoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*create_new_lexer(t_data *data, char *str)
{
	t_lexer	*new;

	new = malloc_track(data, sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->cmd_segment = str;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	check_redirect(const char *cmd, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
			count++;
		else if (count > 0 && cmd[i] != c)
			return (count);
		i++;
	}
	return (count);
}

int	check_redir_error(t_lexer *tmp)
{
	int	count;

	if (!tmp || !tmp->cmd_segment)
		return (-1);
	if (tmp->cmd_segment[0] == '<')
	{
		count = check_redirect(tmp->cmd_segment, '<');
		if (count > 2 || count == 0)
			return (-1);
	}
	else if (tmp->cmd_segment[0] == '>')
	{
		count = check_redirect(tmp->cmd_segment, '>');
		if (count > 2 || count == 0)
			return (-1);
	}
	return (0);
}

t_token	which_redir(t_lexer *tmp)
{
	if (!check_redir_error(tmp))
	{
		if (tmp->cmd_segment[0] == '>' && tmp->cmd_segment[1] == '\0')
			return (REDIRECT_OUT);
		else if (tmp->cmd_segment[0] == '<' && tmp->cmd_segment[1] == '\0')
			return (REDIRECT_IN);
		else if (tmp->cmd_segment[0] == '>' && tmp->cmd_segment[1] == '>')
			return (APPEND_OUT);
		else if (tmp->cmd_segment[0] == '<' && tmp->cmd_segment[1] == '<')
			return (HERE_DOC);
		else if (tmp->cmd_segment[0] == '<' && tmp->cmd_segment[1] == '>')
			return (REDIRECT_INOUT);
		else if (tmp->cmd_segment[0] == '>' && tmp->cmd_segment[1] == '<')
			return (REDIRECT_OUTIN);
	}
	return (-1);
}

void	assign_command_or_argument_token(t_lexer *tmp, t_lexer *first)
{
	if (first->token != CMD)
		tmp->token = CMD;
	else
		tmp->token = ARG;
}
