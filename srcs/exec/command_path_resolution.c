/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path_resolution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:23:53 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @nom: extract_paths_from_env
 * @brief: Extrait les chemins du répertoire à partir de la variable
 * d'environnement PATH.
 *
 * @description:
 * 'extract_paths_from_env' parcourt la liste des variables d'environnement
 * (t_env) pour trouver la variable PATH. Une fois trouvée, la fonction divise
 * la valeur de PATH en un tableau de chaînes de caractères, chacune
 * représentant un chemin de répertoire où les commandes peuvent résider.
 */
char	**extract_paths_from_env(t_env *env_lst, t_data *data)
{
	char	**path;

	path = NULL;
	if (is_env_list_empty_or_null(env_lst))
	{
		return (NULL);
	}
	while (env_lst)
	{
		if (is_env_var_path_name(env_lst))
		{
			path = ft_split_mini(env_lst->var_env_name_and_value \
			+ ft_strlen(ENV_SET_PATH_PREFIX), ':', data);
			return (path);
		}
		env_lst = env_lst->next_var_env_name_and_value;
	}
	return (path);
}

/**
 * @nom: find_command_full_path
 * @brief: Récupère le chemin complet d'une commande en utilisant les variables
 * d'environnement PATH.
 *
 * @description:
 * 'find_command_full_path' prend le nom d'une commande et cherche son chemin
 * complet en utilisant la variable d'environnement PATH. La fonction vérifie
 * si la commande est accessible directement ou doit être recherchée dans les
 * répertoires spécifiés par PATH.
 */
char	*find_command_full_path(char *cmd, t_env *env_lst, t_data *data)
{
	int		index;
	char	*tmp;
	char	**path;

	index = ZERO_INIT;
	if (is_cmd_empty_or_null(cmd))
		return (NULL);
	if (is_cmd_executable(cmd))
		return (cmd);
	else if (is_invalid_direct_path(cmd))
		return (NULL);
	path = extract_paths_from_env(env_lst, data);
	if (path)
	{
		while (path && path[index])
		{
			tmp = ft_strjoin2_mini(path[index], "/", data);
			tmp = ft_strjoin2_mini(tmp, cmd, data);
			if (!access(tmp, F_OK))
				return (tmp);
			index++;
		}
	}
	return (NULL);
}

/**
 * @nom: check_if_cmd_full_path_exec_is_valid
 * @brief: Vérifie si le chemin d'exécution d'une commande est valide.
 *
 * @description:
 * 'check_if_cmd_full_path_exec_is_valid' examine le premier mot d'une
 * lexer (t_lexer) pour déterminer si le chemin de la commande spécifiée est
 * valide en vérifiant si elle existe dans les variables d'environnement. Si
 * le chemin n'est pas trouvé, un message d'erreur est affiché.
 */
int	check_if_cmd_full_path_exec_is_valid(\
t_lexer *lexer, t_exec utils, t_data *data)
{
	if (!find_command_full_path(\
	lexer->cmd_segment, utils.linked_list_full_env_var_copy_alpha, data))
	{
		write(STDERR_FILENO, lexer->cmd_segment, strlen2(lexer->cmd_segment));
		write(\
		STDERR_FILENO, ERR_MSG_CMD_NOT_FOUND, \
		ft_strlen(ERR_MSG_CMD_NOT_FOUND));
		return (EXIT_FAIL);
	}
	return (EXIT_SUCCESS);
}

char	**build_arg_array_from_lexer(t_data *data)
{
	char	**arg;
	int		nb_arg;
	int		index;

	index = ZERO_INIT;
	nb_arg = count_args_until_pipe_for_cmd_array(data->lexer_list);
	arg = malloc_track(data, sizeof(char *) * (nb_arg + 1));
	arg[index++] = data->lexer_list->cmd_segment;
	while (should_continue_lexer_iteration(data->lexer_list, index, nb_arg))
	{
		if (is_lexer_token_cmd_arg(data->lexer_list->next))
			arg[index++] = data->lexer_list->next->cmd_segment;
		data->lexer_list->next = data->lexer_list->next->next;
	}
	arg[index] = NULL;
	return (arg);
}
