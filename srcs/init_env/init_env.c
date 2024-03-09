/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:10:33 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Utilisé dans la fonction init_env_list_with_pwd_if_empty, il crée un
	nouveau noeud pour une variable OLDPWD.
*/
void	malloc_no_env_initial_node(t_data *data, char *str, t_env **env)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		perror(ERR_MEMORY_ALLOCATION);
		return ;
	}
	new_node->var_env_name_and_value = ft_strdup(data, str);
	new_node->next_var_env_name_and_value = NULL;
	*env = new_node;
}

/*
	Est utilisée dans le cas où aucune variable d'environnement n'est passée
	à Minishell. La fonction getwcd est utilisée pour trouver le répertoire
	de travail courant (PWD). Ce path sera mit dans une variable temporaire
	qui sera elle même mise dans un noeud renvoyé à create_env_list_from_array.
	Sans variables d'environnement, certaines fonctionnalités de base du 
	shell pourraient ne pas fonctionner correctement.
*/
t_env	*init_env_list_with_pwd_if_empty(t_data *data, t_env *final)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	tmp = ft_strjoin_free_arg2_with_memory_tracking(ENV_SET_OLDPWD, tmp, data);
	malloc_no_env_initial_node(data, tmp, &final);
	return (final);
}

/**
 * @nom: init_env
 *
 * @description:
 *   Initialise et configure une structure t_exec pour l'environnement
 *   d'exécution.
 *   Cette fonction alloue et prépare une structure contenant les informations
 *   essentielles pour la gestion de l'environnement d'exécution, y compris les
 *   variables d'environnement et les indicateurs d'état.
 *
 * @pourquoi:
 *   - Création d'un environnement d'exécution structuré : La structure t_exec
 *     fournit un moyen organisé de stocker et de gérer les informations
 *     nécessaires à l'exécution du programme, telles que les variables
 *     d'environnement et divers indicateurs d'état.
 *   - Facilitation de l'accès et de la modification : Avec toutes les
 *     informations pertinentes regroupées dans une seule structure, il est
 *     plus facile d'y accéder, de les modifier et de les transmettre entre
 *     les fonctions.
 *   - Préparation pour les opérations futures : L'initialisation des variables
 * 	   et des listes dans cette structure prépare le terrain pour les
 *     opérations ultérieures, telles que la manipulation des variables
 *     d'environnement et la gestion des erreurs.
 *
 * @parametres:
 *   - env: Un tableau de pointeurs vers des chaînes de caractères, représentant
 * 		les 
 *     variables d'environnement du programme.
 *
 * @fonctionnement:
 *   - Alloue de la mémoire pour une nouvelle structure t_exec.
 *   - Si l'allocation échoue, retourne NULL.
 *   - Initialise les variables de la structure, y compris env_lst,
 * 		head_env_lst, 
 *     err, ret et in_here_doc_mode.
 *   - Si 'env' est non-NULL, remplit env_lst avec les variables d'environnement 
 *     en utilisant create_env_list_from_array.
 *   - Retourne un pointeur vers la structure t_exec nouvellement créée.
 *
 * @valeur_de_retour:
 *   - Retourne un pointeur sur la structure t_exec nouvellement initialisée.
 *   - Retourne NULL en cas d'échec de l'allocation mémoire.
 *
 * @erreurs_et_effets_de_bord:
 *   - Si l'allocation mémoire pour 'utils' échoue, la fonction retourne NULL.
 *
 * @exemples_utilisation:
 *   - init_env(environ) pour initialiser l'environnement d'exécution avec les 
 *     variables d'environnement du programme.
 *
 * @dependances:
 *   - malloc_track: Alloue de la mémoire avec suivi.
 *   - create_env_list_from_array: Crée une liste chaînée à partir d'un tableau
 * d'environnements.
 *
 * @graphe_de_flux:
 *   Début
 *     |
 *     v
 *   Allouer de la mémoire pour 'utils'
 *     |
 *     v
 *   'utils' est NULL ?
 *    /       \
 *  VRAI     FAUX
 *    |         |
 *    |         |
 *    v         v
 *   Retourner  Initialiser les variables de 'utils'
 *   NULL       |
 *              v
 *           'env' est non-NULL ?
 *            /        \
 *          VRAI      FAUX
 *            |         |
 *            |         |
 *            v         v
 *          Remplir    Assigner NULL à 'utils->env_lst'
 *          'utils->env_lst' avec 'env'
 *            |
 *            v
 *         Retourner 'utils'
 */
t_exec	*init_env(t_data *data, char **env)
{
	t_exec	*utils;

	utils = malloc_track(data, sizeof(t_exec));
	if (!utils)
		return (NULL);
	utils->linked_list_full_env_var_copy_alpha = NULL;
	if (env)
		utils->linked_list_full_env_var_copy_alpha = \
		create_env_list_from_array(data, env);
	utils->head_env_lst = utils->linked_list_full_env_var_copy_alpha;
	utils->is_this_an_exec_in_heredoc = ZERO_INIT;
	return (utils);
}
