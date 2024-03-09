/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes_and_fds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:19:55 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @nom: closes_ends_of_pipe
 * @brief: Ferme les deux extrémités d'un pipe.
 */
int	closes_ends_of_pipe(int *fd)
{
	if (fd[PIPE_READ_END] > 0)
		close(fd[PIPE_READ_END]);
	if (fd[PIPE_WRITE_END] > 0)
		close(fd[PIPE_WRITE_END]);
	return (1);
}

/**
 * @nom: close_file_descriptors_in_linked_list
 * @brief: Ferme les descripteurs de fichier de tous les nœuds dans une liste
 * de nœuds.
 *
**/
int	close_file_descriptors_in_linked_list(t_data *data)
{
	data->utils->node = data->utils->head_cmd_lst;
	while (data->utils->node)
	{
		if (data->utils->node->input_fd > 1)
			close(data->utils->node->input_fd);
		if (data->utils->node->output_fd > 1)
			close(data->utils->node->output_fd);
		data->utils->node = data->utils->node->next;
	}
	return (1);
}
