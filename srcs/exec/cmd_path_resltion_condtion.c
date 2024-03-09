/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_resltion_condtion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:58:25 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_env_var_path_name(t_env *env)
{
	return (!ft_strncmp(\
	env->var_env_name_and_value, ENV_SET_PATH_PREFIX, \
	ft_strlen(ENV_SET_PATH_PREFIX)));
}

/**
 * @brief Vérifie si un chemin direct spécifié pour une commande est invalide.
 *
 * @param cmd Le chemin de la commande à vérifier.
 * @return true Si le chemin direct est invalide (non exécutable et commence
 * par un '/'), sinon false.
 */
bool	is_invalid_direct_path(const char *cmd)
{
	return (access(cmd, X_OK) && *cmd == '/');
}
