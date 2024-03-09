/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 18:11:33 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @nom: setup_input_redirection
 *
 * @description:
 * Configure la redirection d'entrée pour un nœud de commande, basée sur une
 * liste de lexèmes. Cette configuration est fondamentale dans un shell pour
 * diriger l'entrée des commandes depuis des fichiers ou d'autres sources,
 * comme les here-docs.
 *
 * @parametres:
 * - node: t_node *node, pointeur vers le nœud de commande à configurer.
 * - lexer_lst: t_lexer *lexer_lst, pointeur vers le début de la liste de
 * lexèmes.
 *
 * @fonctionnement:
 * Initialise les variables de redirection d'entrée dans le nœud (`input_fd`,
 * `is_input_redirection_failed`). Parcourt la liste de lexèmes pour configurer
 * les redirections d'entrée normales et les here-docs.
 * Utilise `configure_here_doc_input` pour gérer les here-docs et
 * `handle_redirect_input_error` en cas d'échec de redirection d'entrée.
 *
 * Pourquoi configurer la redirection d'entrée ?
 * - Contrôle des données entrantes : Oriente l'entrée des commandes depuis
 * des fichiers ou des sources spécifiques, permettant une plus grande
 * flexibilité dans l'exécution des commandes.
 * - Gestion des here-docs : Permet d'utiliser des here-docs pour fournir des
 * entrées multi-lignes, une fonctionnalité importante dans les scripts shell
 * et les commandes interactives.
 * - Gestion des erreurs : Détecte et gère les problèmes de redirection pour
 * éviter les comportements imprévus et les erreurs silencieuses.
 *
 * @valeur_retour: 
 * Aucune (void). Modifie le nœud de commande en place.
 *
 * @erreurs: 
 * - Écrit un message d'erreur si l'ouverture du fichier ou la configuration
 * du here-doc échoue.
 *
 * @exemple_utilisation:
 *   t_node *node = create_node();
 *   t_lexer *lexer_lst = create_lexer_list("commande < fichier.txt");
 *   setup_input_redirection(node, lexer_lst);
 *
 * @dependances: 
 *   - configure_here_doc_input pour les here-docs.
 *   - handle_redirect_input_error pour la gestion des erreurs.
 *   - ft_write_fd pour l'écriture des messages d'erreur.
 *
 * @graphe_de_flux:
 *   Début
 *     |
 *     v
 *   Initialisation des champs de redirection d'entrée dans node
 *     |
 *     v
 *   Parcourir lexer_lst
 *     |
 *     v
 *   lexer_lst est-il NULL ou token == PIPE ?
 *  /       \
 * OUI      NON
 *  |        |
 *  |        v
 *  |     Redirection d'entrée normale ou here-doc ?
 *  |    /         \
 *  |  NORMAL    HERE-DOC
 *  |    |          |
 *  |    v          v
 *  |  Gérer     Gérer here-doc
 *  |  avec      avec configure_here_doc_input
 *  |  handle_redirect_input_error
 *  |    |
 *  \----/
 *     |
 *     v
 *   Passer au lexème suivant
 *     |
 *     v
 *   Fin
 */
void	setup_input_redirection(t_node *node, t_lexer *lexer_lst, t_data *data)
{
	node->input_fd = INPUT_FD_NOT_SET;
	node->is_input_redirection_failed = ZERO_INIT;
	while (is_current_token_not_pipe(lexer_lst))
	{
		if (is_input_redirection_followed_by_token_fd(lexer_lst))
		{
			if (is_input_fd_open_ready_for_read(node))
				close(node->input_fd);
			if (is_next_word_missing(lexer_lst))
				node->is_input_redirection_failed = TRUE;
			if (is_next_word_existing_and_readable(lexer_lst))
				node->input_fd = open(lexer_lst->next->cmd_segment, O_RDONLY);
			else
				handle_redirect_input_error(node, lexer_lst);
		}
		configure_here_doc_input(node, lexer_lst, data);
		lexer_lst = lexer_lst->next;
	}
}

/**
 * @nom: append_output_redirection
 *
 * @description:
 * Configure une redirection de sortie de type append pour un nœud de
 * commande, en fonction des lexèmes fournis. Cette opération est essentielle
 * pour ajouter des sorties à la fin d'un fichier existant, sans écraser son
 * contenu actuel, dans un contexte de shell.
 *
 * @parametres:
 * - node: t_node *node, pointeur vers le nœud de commande à configurer.
 * - lex_lst: t_lexer *lex_lst, pointeur vers la liste de lexèmes.
 * - is_output_redirection_feasible: int *is_output_redirection_feasible,
 * pointeur vers l'indicateur de présence de redirection de sortie.
 *
 * @fonctionnement:
 * Vérifie si les lexèmes indiquent une redirection de sortie de type append
 * (APPEND_OUT). Si oui, ferme la sortie existante si ouverte, puis tente
 * d'ouvrir le fichier de redirection en mode append. En cas d'échec
 * d'ouverture ou d'absence de nom de fichier, écrit un message d'erreur et
 * met à jour l'indicateur d'échec (`output_redirection_error_id`).
 * - `ft_write_fd` est utilisée pour écrire les messages d'erreur.
 * - Gère également les cas d'échec d'accès au fichier.
 *
 * Pourquoi gérer la redirection de sortie de type append ?
 * - Ajout de données : Permet d'ajouter des sorties à un fichier existant sans
 * écraser son contenu, ce qui est crucial pour les journaux ou la
 * concaténation de données.
 * - Précision de la redirection : Fournit un contrôle plus fin sur la manière
 * dont les données sont ajoutées aux fichiers, en respectant le contenu
 * préexistant.
 * - Flexibilité dans l'exécution des commandes : Offre la possibilité de
 * manipuler la sortie des commandes pour des besoins spécifiques, comme
 * l'ajout de logs ou la collecte de données sur une période.
 *
 * @valeur_retour: 
 * Aucune (void). Modifie le nœud de commande en place.
 *
 * @erreurs: 
 * - Écrit un message d'erreur si l'ouverture du fichier échoue ou si l'accès
 * est refusé.
 *
 * @exemple_utilisation:
 *   t_node *node = create_node();
 *   t_lexer *lex_lst = create_lexer_list("commande >> fichier.txt");
 *   append_output_redirection(
 *			node, lex_lst, &node->is_output_redirection_feasible);
 *
 * @dependances: 
 *   - ft_write_fd pour écrire les messages d'erreur.
 *
 * @graphe_de_flux:
 *   Début
 *     |
 *     v
 *   Vérifier la présence d'une redirection de sortie append
 *     |
 *     v
 *   Condition de redirection append remplie ?
 *  /       \
 * OUI      NON
 *  |        |
 *  |        v
 *  |     Fin de la fonction
 *  |
 *  v
 * Fermer la sortie existante si ouverte
 *  |
 *  v
 * Ouvrir le fichier de redirection en mode append
 *  |
 *  v
 * Ouverture réussie ?
 *  /       \
 * OUI      NON
 *  |        |
 *  |        v
 *  |     Écrire message d'erreur avec ft_write_fd
 *  |        |
 *  |        v
 *  |     Mettre à jour node->output_redirection_error_id
 *  |
 *  v
 * Accès en écriture refusé ?
 *  /       \
 * OUI      NON
 *  |        |
 *  |        v
 *  |     Mettre à jour node->output_redirection_error_id
 *  | 
 *  v
 * Mettre à jour *is_output_redirection_feasible
 *  |
 *  v
 * Fin
 */
void	append_output_redirection(\
t_node *node, t_lexer *lex_lst, int *is_output_redirection_feasible)
{
	if (is_append_out_followed_by_fd_token(lex_lst))
	{
		if (is_output_fd_open_for_closing(node))
			close (node->output_fd);
		if (is_next_lexeme_word_existing(lex_lst))
			node->output_fd = open(\
			lex_lst->next->cmd_segment, append_to_file_flags(), \
			PERM_O_RW_G_R_OT_R);
		else
		{
			ft_write_fd(ERR_AMB_REDIRECT, STDERR_FILENO);
			node->output_redirection_error_id = \
			OUTPUT_ABSENCE_OF_TARGET_ERROR_CODE;
		}
		if (is_output_append_redirection_error_detected(node, lex_lst))
			node->output_redirection_error_id = \
			OUTPUT_TARGET_ACCESS_ERROR_CODE;
		*is_output_redirection_feasible = TRUE;
	}
}

bool	is_next_command_segment_present(t_lexer *lex_lst)
{
	return (lex_lst->next && lex_lst->next->cmd_segment);
}

/**
 * @nom: normal_output_redirection
 *
 * @description:
 * Configure une redirection de sortie standard pour un nœud de commande en se
 * basant sur une liste de lexèmes. Cette opération est cruciale pour diriger
 * la sortie des commandes vers des fichiers ou d'autres processus dans un
 * environnement de shell.
 *
 * @parametres:
 * - node: t_node *node, pointeur vers le nœud de commande à configurer.
 * - lex_lst: t_lexer *lex_lst, pointeur vers le début de la liste de lexèmes.
 *
 * @fonctionnement:
 * Vérifie si les lexèmes actuels indiquent une redirection de sortie
 * standard (REDIRECT_OUT). Si oui, ferme la sortie existante si elle est
 * ouverte,puis tente d'ouvrir le fichier de redirection spécifié. Si
 * l'ouverture échoue ou si le nom du fichier n'est pas donné, écrit un
 * message d'erreur et met à jour l'indicateur d'échec de sortie
 * (`output_redirection_error_id`).
 *
 * Pourquoi gérer la redirection de sortie standard ?
 * - Contrôle de flux : Permet de rediriger la sortie des commandes vers des
 * fichiers, ce qui est essentiel pour enregistrer des résultats ou chaîner
 * des commandes.
 * - Gestion des erreurs : Assure que les échecs de redirection sont détectés
 * et traités, évitant ainsi les comportements imprévus et les erreurs
 * silencieuses.
 * - Flexibilité dans l'exécution des commandes : Offre la possibilité de
 * manipuler la sortie des commandes pour des besoins spécifiques, comme la
 * création de logs.
 *
 * @valeur_retour: 
 * Aucune (void). Modifie le nœud de commande en place.
 *
 * @erreurs: 
 * - Écrit un message d'erreur si l'ouverture du fichier échoue ou si l'accès
 * est refusé.
 *
 * @exemple_utilisation:
 * t_node *node = create_node();
 * t_lexer *lex_lst = create_lexer_list("commande > fichier.txt");
 * normal_output_redirection(node, lex_lst);
 *
 * @dependances: 
 *  - ft_write_fd pour écrire les messages d'erreur.
 *
 * @graphe_de_flux:
 *   Début
 *     |
 *     v
 *   Vérifier la présence d'une redirection de sortie standard
 *     |
 *     v
 *   Condition de redirection standard remplie ?
 *  /       \
 * OUI      NON
 *  |        |
 *  |        v
 *  |     Fin de la fonction
 *  |
 *  v
 * Fermer la sortie existante si ouverte
 *  |
 *  v
 * Ouvrir le fichier de redirection
 *  |
 *  v
 * Ouverture réussie ?
 *  /       \
 * OUI      NON
 *  |        |
 *  |        v
 *  |     Écrire message d'erreur avec ft_write_fd
 *  |        |
 *  |        v
 *  |     Mettre à jour node->output_redirection_error_id
 *  |
 *  v
 * Accès en écriture refusé ?
 *  /       \
 * OUI      NON
 *  |        |
 *  |        v
 *  |     Mettre à jour node->output_redirection_error_id
 *  | 
 *  v
 * Mettre à jour node->is_output_redirection_feasible
 *  |
 *  v
 * Fin
 */
void	normal_output_redirection(t_node *node, t_lexer *lex_lst)
{
	if (is_redirect_out_followed_by_fd_token(lex_lst))
	{
		if (is_output_fd_open_for_closing(node))
			close (node->output_fd);
		if (is_next_command_segment_present(lex_lst))
			node->output_fd = open(\
			lex_lst->next->cmd_segment, out_to_file_flags(), \
			PERM_O_RW_G_R_OT_R);
		else
		{
			ft_write_fd(ERR_AMB_REDIRECT, STDERR_FILENO);
			node->output_redirection_error_id = \
			OUTPUT_ABSENCE_OF_TARGET_ERROR_CODE;
		}
		if (is_normal_output_redirection_error_detected(node, lex_lst))
			node->output_redirection_error_id = \
			OUTPUT_TARGET_ACCESS_ERROR_CODE;
		node->is_output_redirection_feasible = TRUE;
	}
}

/**
 * @nom: setup_output_redirection
 *
 * @description:
 * Configure la redirection de sortie pour un nœud de commande en utilisant
 * une liste de lexèmes.
 *
 * @parametres:
 * - node: t_node *node, pointeur vers le nœud de commande.
 * - lex_lst: t_lexer *lex_lst, pointeur vers le début de la liste de lexèmes.
 *
 * @fonctionnement:
 * Initialise les champs de redirection de sortie du nœud
 * (`is_output_redirection_feasible`, `out`, `output_redirection_error_id`).
 * Parcourt la liste de lexèmes, appelant `normal_output_redirection` et
 * `append_output_redirection` pour chaque lexème. Si une redirection est
 * présente mais échoue, un message d'erreur est généré et les indicateurs de
 * redirection sont réinitialisés. La boucle se poursuit jusqu'à la rencontre
 * d'un token PIPE ou la fin de la liste.
 * - `normal_output_redirection` gère les redirections de sortie normales.
 * - `append_output_redirection` gère les redirections de sortie de type
 * append.
 *
 * Pourquoi cette fonction est-elle importante ?
 * La fonction `setup_output_redirection` est essentielle dans un
 * environnement de shell pour rediriger la sortie des commandes vers des
 * fichiers ou d'autres processus. Cette capacité de redirection offre une
 * flexibilité cruciale pour le contrôle des données générées par les
 * commandes. Voici quelques points clés :
 *   
 * - **Contrôle de la Sortie des Commandes** : La redirection de sortie permet
 * aux utilisateurs de diriger les données générées par les commandes vers des
 * fichiers ou d'autres destinations, augmentant ainsi les options pour
 * manipuler et enregistrer les sorties des commandes.
 * - **Gestion des Redirections Multiples** : La fonction gère à la fois les
 * redirections normales (écrasement) et les redirections de type append
 * (ajout), donnant aux utilisateurs la flexibilité de choisir comment gérer
 * la sortie des commandes en fonction de leurs besoins.
 * - **Robustesse et Fiabilité** : En traitant les erreurs de redirection et
 * en réinitialisant les indicateurs appropriés, la fonction assure que le
 * shell reste stable et fiable, même dans des situations où les redirections
 * échouent ou sont mal configurées.
 * 
 * @valeur_retour: 
 * Aucune (void). Modifie le nœud de commande en place.
 *
 * @erreurs: 
 * - Génère un message d'erreur si la redirection de sortie échoue.
 *
 * @exemple_utilisation:
 *   t_node *node = create_node();
 *   t_lexer *lex_lst = create_lexer_list("cmd > file.txt | cmd2");
 *   setup_output_redirection(node, lex_lst);
 *
 * @dependances: 
 *   - normal_output_redirection
 *   - append_output_redirection
 *
 * @graphe_de_flux:
 *   Début
 *     |
 *     v
 *   Initialisation des champs de redirection dans node
 *     |
 *     v
 *   Parcourir lex_lst
 *     |
 *     v
 *   lex_lst est-il NULL ou token == PIPE ?
 *  /       \
 * OUI      NON
 *  |        |
 *  |        v
 *  |     Appeler normal_output_redirection
 *  |        |
 *  |        v
 *  |     Appeler append_output_redirection
 *  |        |
 *  |        v
 *  |     Redirection échouée ?
 *  |    /       \
 *  |   OUI      NON
 *  |    |        |
 *  |    v        v
 *  |  Générer  Passer au lexème suivant
 *  |  message d'erreur
 *  |    |
 *  |    v
 *  |  Réinitialiser les indicateurs de redirection
 *  |    |
 *  \----/
 *     v
 *   Fin
 */
void	setup_output_redirection(t_node *node, t_lexer *lex_lst)
{
	node->is_output_redirection_feasible = ZERO_INIT;
	node->output_fd = OUTPUT_FD_NOT_CONFIGURED;
	node->output_redirection_error_id = 0;
	while (is_current_token_not_pipe(lex_lst))
	{
		normal_output_redirection(node, lex_lst);
		append_output_redirection(\
		node, lex_lst, &node->is_output_redirection_feasible);
		if (is_output_redirection_error_detected(node))
		{
			node->is_output_redirection_feasible = FALSE;
			perror(OUT_FILE);
		}
		lex_lst = lex_lst->next;
	}
}
