/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:33:56 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @nom: handle_redirect_input_error
 *
 * @description:
 * Gère les erreurs de redirection d'entrée pour un nœud de commande.
 * Cette fonction est utilisée pour signaler des erreurs lors de la tentative
 * de redirection d'entrée, comme l'échec de l'ouverture d'un fichier.
 */
void	handle_redirect_input_error(t_node *node, t_lexer *lexer_lst)
{
	if (is_first_input_redirection_error(node))
	{
		node->input_fd = INPUT_FD_REDIRECTION_FAIL;
		perror(lexer_lst->next->cmd_segment);
	}
	else
	{
		node->input_fd = INPUT_FD_REDIRECTION_FAIL;
		ft_write_fd(ERR_AMB_REDIRECT, STDERR_FILENO);
	}
}

/**
 * @nom: ft_strdup
 *
 * @description:
 * Duplique une chaîne de caractères en allouant de la mémoire pour la
 * nouvelle copie. Cette fonction est essentielle pour créer des copies
 * indépendantes de chaînes de caractères, souvent utilisées dans les
 * environnements où la manipulation des données originales n'est pas
 * souhaitée ou possible.
 */
char	*ft_strdup(t_data *data, char *src)
{
	int		index;
	char	*dest;

	index = ZERO_INIT;
	if (!src)
		return (NULL);
	while (src[index])
		index++;
	dest = malloc_track(data, sizeof(char) * index + sizeof('\0'));
	if (!dest)
		return (NULL);
	index = 0;
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

/**
 * @nom: is_token_type_cmd
 *
 * @description:
 * Vérifie la présence d'une commande dans une liste de lexèmes. Cette
 * fonction est cruciale pour déterminer si un ensemble de lexèmes représente
 * une commande valide dans un environnement de shell.
 */
int	is_token_type_cmd(t_lexer *lexer_lst)
{
	while (lexer_lst)
	{
		if (is_current_lexer_token_cmd(lexer_lst))
			return (CMD_FOUND);
		lexer_lst = lexer_lst->next;
	}
	return (CMD_NOT_FOUND);
}

/**
 * @nom: count_cmd_in_lexer_linked_list
 *
 * @description:
 * Compte le nombre de commandes dans une liste de lexèmes. Cette fonction est
 * essentielle pour déterminer combien de commandes individuelles sont
 * présentes dans une entrée de shell, ce qui est crucial pour la préparation
 * et l'exécution de commandes dans un environnement de shell.
 */
int	count_cmd_in_lexer_linked_list(t_lexer *lexer_list)
{
	int	cmd_count;

	cmd_count = ZERO_INIT;
	while (lexer_list)
	{
		if (is_current_lexer_token_cmd(lexer_list))
			cmd_count++;
		lexer_list = lexer_list->next;
	}
	return (cmd_count);
}

/**
 * @nom: count_pipe_or_end_in_lexer_linked_list
 *
 * @description:
 * Compte le nombre de nœuds (commandes ou pipelines) dans une liste de
 * lexèmes. Cette fonction est cruciale pour déterminer la structure et le
 * nombre de commandes à exécuter dans un environnement de shell.
 */
int	count_pipe_or_end_in_lexer_linked_list(t_lexer *lexer_list)
{
	int	index;

	index = ZERO_INIT;
	while (lexer_list)
	{
		if (is_pipe_or_end_of_lexer_linked_list(lexer_list))
			index++;
		lexer_list = lexer_list->next;
	}
	return (index);
}
