/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:11:55 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_quotes(char *str, t_data *data)
{
	int	i;

	i = ZERO_INIT;
	data->is_sing_quot = 0;
	data->is_doub_quot = 1;
	while (str[i])
	{
		if (str[i] == '"' && !data->is_sing_quot && !data->is_doub_quot)
			data->is_doub_quot = 1;
		else if (str[i] == '"' && !data->is_sing_quot && data->is_doub_quot)
			data->is_doub_quot = 0;
		else if (str[i] == '\'' && !data->is_sing_quot && data->is_doub_quot)
			data->is_sing_quot = 1;
		else if (str[i] == '\'' && data->is_sing_quot && data->is_doub_quot)
			data->is_sing_quot = 0;
		i++;
	}
	if (data->is_sing_quot == data->is_doub_quot)
	{
		printf("minishell: syntax error quote not closed\n");
		return (0);
	}
	return (1);
}

int	check_redir(char *str)
{
	int	i;

	i = ZERO_INIT;
	if (str[i + 1] == '\0')
		return (0);
	if ((str[i] == '>' && str[i + 1] == '>') \
	|| (str[i] == '>' && str[i + 1] == '<') \
	|| (str[i] == '<' && str[i + 1] == '<') \
	|| (str[i] == '<' && str[i + 1] == '>'))
	{
		if (str[i + 2] == '\0')
			return (0);
	}
	return (1);
}

int	base_check(char *str)
{
	int	i;

	i = ZERO_INIT;
	if (str[0] == '|' && str[1] == '|')
	{
		printf("minishell: syntax error near unexpected token `||'\n");
		return (0);
	}
	if (str[0] == '|')
	{
		printf("minishell:  syntax error near unexpected token `|'\n");
		return (0);
	}
	if (str[i] == '<' || str[i] == '>')
	{
		if (!check_redir(str))
		{
			printf("syntax error near unexpected token\n");
			return (0);
		}
	}
	return (1);
}

int	ft_cloporte(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer_list;
	while (tmp != NULL)
	{
		if (tmp->token == REDIRECT_OUT || tmp->token == APPEND_OUT \
		|| tmp->token == REDIRECT_OUTIN || tmp->token == REDIRECT_IN \
		|| tmp->token == HERE_DOC || tmp->token == REDIRECT_INOUT)
		{
			tmp = tmp->next;
			if (tmp == NULL || tmp->cmd_segment[0] == '\0')
			{
				printf("syntax error near unexpected token\n");
				return (0);
			}
		}
		tmp = tmp->next;
	}
	tmp = data->lexer_list;
	return (1);
}

int	ft_parser(t_data *data)
{
	int	count;

	count = 1;
	if (!ft_check_quotes(data->minishell_input_cmd, data))
		count = 0;
	else if (!base_check(data->minishell_input_cmd))
		count = 0;
	else if (!pipe_parse(data))
		count = 0;
	else if (!ft_cloporte(data))
		count = 0;
	else if (!ft_arrow(data))
		count = 0;
	else if (!ft_tiret(data->minishell_input_cmd))
		count = 0;
	else if (!chevron_pipe(data->minishell_input_cmd))
		count = 0;
	if (count == 0)
	{
		g_globi = 2;
		return (0);
	}
	return (1);
}
