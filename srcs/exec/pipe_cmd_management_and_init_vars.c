/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd_management_and_init_vars.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:24:44 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @nom: reaches_next_cmd_preceded_by_pipe
 * @brief: Avance dans la liste de lexèmes jusqu'à la prochaine commande.
 *
 * @description:
 * Parcourt une liste de lexèmes (t_lexer) et avance jusqu'à ce qu'elle trouve
 * un lexème représentant un pipe (PIPE), indiquant la fin d'une commande et le
 * début de la suivante. Cette fonction est utilisée pour naviguer à travers
 * les différentes commandes dans un environnement de shell.
 */
t_lexer	*reaches_next_cmd_preceded_by_pipe(t_lexer *lexer_list)
{
	while (is_current_token_not_pipe(lexer_list))
		lexer_list = lexer_list->next;
	if (is_current_token_pipe(lexer_list))
		lexer_list = lexer_list->next;
	return (lexer_list);
}

/**
 * @nom: count_args_until_pipe_for_cmd_array
 *
 * @description: Compte le nombre d'arguments dans une liste de lexèmes
 * jusqu'à un token de type PIPE.
 */
int	count_args_until_pipe_for_cmd_array(t_lexer *lexer_list)
{
	int	index;

	index = 1;
	while (is_current_token_not_pipe(lexer_list))
	{
		if (is_current_token_cmd_arg(lexer_list))
			index++;
		lexer_list = lexer_list->next;
	}
	return (index);
}

/**
 * @nom: initialize_pid_array_to_zero
 * @brief: Initialise un tableau de Process ID (PID) à zéro.
 *
 * @description:
 * La fonction parcourt un tableau de type pid_t (généralement utilisé pour
 * stocker des identifiants de processus) et initialise chaque élément à zéro.
 * Cette initialisation est essentielle pour assurer que le tableau ne contient
 * pas de valeurs indésirables ou non définies avant son utilisation.
 */
void	initialize_pid_array_to_zero(pid_t *pid_array, int num_nodes)
{
	while (num_nodes-- > 0)
		*(pid_array++) = 0;
}

/**
 * @nom: init_fd_and_status_vars
 * @brief: Initialise des variables utilisées dans la gestion des processus et
 * des descripteurs de fichier.
 *
 * @description:
 * Cette fonction initialise plusieurs variables importantes utilisées dans le
 * cadre de la gestion des processus et des descripteurs de fichier dans un
 * shell ou un système similaire. Elle met à zéro ou initialise à des valeurs
 * par défaut les variables passées en paramètre.
 */
void	init_fd_and_status_vars(int *fd, int *y, int *wstatus)
{
	*wstatus = ZERO_INIT;
	y[0] = ZERO_INIT;
	y[1] = -1;
	fd[0] = ZERO_INIT;
	fd[1] = ZERO_INIT;
}
