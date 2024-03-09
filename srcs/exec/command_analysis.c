/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoure <lgoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/24 14:41:59 by lgoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @nom: is_exact_command_match
 *
 * @description:
 * Compare un mot de la liste de lexèmes avec une commande spécifiée pour
 * vérifier si elles sont identiques en termes de contenu et de longueur. Cette
 * fonction est essentielle pour identifier des commandes spécifiques dans un
 * interpréteur de commandes ou un shell, assurant ainsi que les commandes
 * entrées correspondent exactement à celles attendues, ni plus courtes ni plus
 * longues.
 */
int	is_cmd_match(\
t_lexer *lexer_lst, const char *command, int command_length)
{
	return (!ft_strncmp(lexer_lst->cmd_segment, command, command_length) \
	&& strlen2(lexer_lst->cmd_segment) == command_length);
}

/**
 * @fonction: is_built_in_command
 * @breve_description: Détermine si un mot dans une liste de lexèmes
 * représente une commande intégrée.
 */
int	is_built_in_command(t_lexer *lexer_lst)
{
	if (lexer_lst == NULL || lexer_lst->cmd_segment == NULL)
		return (0);
	return (is_cmd_match(\
	lexer_lst, CMD_PRINT_DIRCT, ft_strlen(CMD_PRINT_DIRCT)) \
	|| is_cmd_match(\
	lexer_lst, CMD_ECHO, ft_strlen(CMD_ECHO)) \
	|| is_cmd_match(\
	lexer_lst, CMD_ENV_VARS, ft_strlen(CMD_ENV_VARS)) \
	|| is_cmd_match(\
	lexer_lst, CMD_UNSET_VARS, ft_strlen(CMD_UNSET_VARS)) \
	|| is_cmd_match(\
	lexer_lst, CMD_CHANG_DIRCT, ft_strlen(CMD_CHANG_DIRCT)) \
	|| is_cmd_match(\
	lexer_lst, CMD_EXPORT_VARS, ft_strlen(CMD_EXPORT_VARS)) \
	|| is_cmd_match(\
	lexer_lst, CMD_EXIT_SHELL, ft_strlen(CMD_EXIT_SHELL)));
}

/**
 * @fonction: should_continue_execution
 * @breve_description: Détermine si l'exécution doit se poursuivre en fonction
 * de l'état actuel.
 */
int	should_continue_execution(t_data *data, int *y)
{
	return (data->utils->node \
	&& data->utils->node->is_command_present == 1 \
	&& ++y[1] >= 0 \
	&& data->utils->heredoc_ctrl_c_uninterrupted);
}

/**
 * @fonction: check_redirection_validity_in_node
 * @breve_description: Évalue la validité d'une redirection pour un nœud donné.
 */
int	check_redirection_validity_in_node(t_node *node)
{
	return (node->input_fd != INPUT_FD_REDIRECTION_FAIL \
	&& node->output_redirection_error_id != \
	OUTPUT_ABSENCE_OF_TARGET_ERROR_CODE);
}

/**
 * @fonction: find_next_command_in_lexer
 * @breve_description: Trouve la prochaine commande dans une liste de lexèmes.
 */
t_lexer	*find_next_command_in_lexer(t_lexer *lexer_list)
{
	while (lexer_list && lexer_list->token != CMD)
		lexer_list = lexer_list->next;
	return (lexer_list);
}
