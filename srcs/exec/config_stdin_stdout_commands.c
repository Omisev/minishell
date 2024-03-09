/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_stdin_stdout_commands.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:24:14 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_fd_valid_for_close(int fd)
{
	return (fd > 0);
}

bool	is_fd_set_for_redirection(int fd)
{
	return (fd >= 0);
}

/**
 * @nom: configure_stdin_redirection_for_command
 * @brief: Configure la redirection de l'entrée standard pour une commande.
 *
 * @description:
 * Cette fonction gère la redirection de l'entrée standard pour une commande
 * donnée. Elle redirige l'entrée standard vers un descripteur de fichier
 * spécifié, en se basant sur la configuration du nœud de commande actuel et la
 * position de la commande dans la séquence de commandes. C'est un composant
 * crucial dans la gestion des pipelines et des redirections d'entrée dans un
 * shell.
 */
void	configure_stdin_redirection_for_command(t_exec utils, int count)
{
	if (is_fd_set_for_redirection(utils.node->input_fd))
	{
		dup2(utils.node->input_fd, STDIN_FILENO);
		if (is_fd_valid_for_close(utils.node->input_fd))
			close(utils.node->input_fd);
		if (utils.previous_fd)
			close(utils.previous_fd);
	}
	else if (count)
	{
		dup2(utils.previous_fd, STDIN_FILENO);
		if (is_fd_valid_for_close(utils.previous_fd))
			close(utils.previous_fd);
	}
}

bool	is_not_last_command_and_fd_open(int count, int total_cmds, int fd)
{
	return (count != total_cmds - 1 && fd > 0);
}

/**
 * @nom: configure_stdout_redirection_for_command
 * @brief: Gère la redirection de la sortie standard pour une commande.
 *
 * @description:
 * Redirige la sortie standard vers un descripteur de fichier spécifié, en
 * fonction de la configuration du nœud de commande actuel et de la position de
 * la commande dans la séquence globale des commandes. Cette fonction est
 * utilisée pour rediriger correctement la sortie des commandes dans un
 * pipeline ou vers un fichier.
 */
void	configure_stdout_redirection_for_command(\
t_exec utils, int *fd, int count)
{
	if (is_fd_valid_for_close(utils.node->output_fd))
	{
		dup2(utils.node->output_fd, STDOUT_FILENO);
		if (is_fd_valid_for_close(utils.node->input_fd))
			close (utils.node->input_fd);
	}
	else if (is_not_last_command_and_fd_open(\
	count, utils.nb_cmd_in_lst, fd[1]))
		dup2(fd[1], STDOUT_FILENO);
	if (is_fd_valid_for_close(fd[1]))
		close(fd[1]);
	if (is_fd_valid_for_close(fd[0]))
		close (fd[0]);
}
