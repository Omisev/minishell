/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoure <lgoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/25 13:52:47 by lgoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = ZERO_INIT;
	if (!s1 || !s2 || !s1[i] || !s2[i])
		return (1);
	while (s1 && s2 && s1[i] && s2[i]
		&& s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

/*
	on initialise a i + 2 pour sauter les deux premier elem du tableau (-n)
	puis on regarde si il y a un -n en argument et ne l'imprime pas
	si il le trouve et imprime si ce n'est pas en -n
	en gros ecrit les argument du echo avec un -n
*/
void	display_echo_arg(char **tab, int i, t_data *data)
{
	int	j;

	j = 0;
	i = i + 1;
	if (data->utils->node->output_fd > 0)
		write_echo_fd(tab, i + 1, data);
	else if (!data->utils->node->output_redirection_error_id)
	{
		while (tab[++i])
		{
			if (j == 1)
			{
				printf("%s", tab[i]);
				if (tab[i + 1])
					printf(" ");
			}
			else if (ft_strcmp(tab[i], "-n"))
			{
				printf("%s", tab[i]);
				if (tab[i + 1])
					printf(" ");
				j = 1;
			}
		}
	}
}

/*
	regarde tout les arguments et cherche un CMD ou un ARG puis quand
	c'est trouver passe au prochain
*/
void	get_words(t_lexer *lexer_lst, char **tab, int *i)
{
	while ((lexer_lst) && (lexer_lst->token == CMD || lexer_lst->token == ARG))
	{
		tab[(*i)++] = lexer_lst->cmd_segment;
		lexer_lst = lexer_lst->next;
	}
}

/*
	elle decide ou afficher les arugment de echo separer par des space
	la fonction commence par regarder si elle doit ecrire sur une sortie special
	si c'est le cas elle ajoute une nouvelle ligne a la fin
	si la sortie n'es pas special elle appel process_echo2
	En gros elle decide ou ecrire et gere les erreurs
*/
void	process_echo(char **tab, int i, t_data *data)
{
	int	j;

	j = ZERO_INIT;
	if (data->utils->node->output_fd > 0)
	{
		if (procc_in_echo_fd(tab, i, j, data) == -1)
			return ;
		ft_write_fd("\n", data->utils->node->output_fd);
	}
	else
		procc_in_echo_std(tab, i, data);
	g_globi = 0;
}

/*
	la fonction ecri chaque argument apres le premier et ajoute un
	espace entre chaque argument qui suivent
	puis ajoute une nouvelle ligne a la fin
*/
void	procc_in_echo_std(char **tab, int i, t_data *data)
{
	int	j;

	j = ZERO_INIT;
	if (!data->utils->node->output_redirection_error_id)
	{
		while (tab[i])
		{
			if (j)
				printf(" %s", tab[i++]);
			else
				printf("%s", tab[i++]);
			j++;
		}
		printf("\n");
	}
}
