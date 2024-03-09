/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:55:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/01/22 17:58:03 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	elle cherche si il y un pwd, si il y a que pwd elle appel display_pwd
	sinon elle appel display_pwd_error
*/
int	get_pwd(char *tab, t_data *data)
{
	char	**str;

	str = ft_split_mini(tab, ' ', data);
	if (tab && strcmp(str[0], CMD_PRINT_DIRCT) == 0)
	{
		if (str[1] == NULL)
			display_pwd(data);
		else
			display_pwd_error(data);
	}
	return (0);
}

/*
	elle va afficher la ou on est (repertoir de travail actuel)
	use getcwd pour ca et gere les erreur si il echoue
*/
void	display_pwd(t_data *data)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		ft_printf("error retrieving current directory: " \
		"No such file or directory\n");
		g_globi = 1;
		free(tmp);
		return ;
	}
	if (data->utils->node->output_fd > 0)
	{
		ft_write_fd(tmp, data->utils->node->output_fd);
		ft_write_fd("\n", data->utils->node->output_fd);
	}
	else if (!data->utils->node->output_redirection_error_id)
	{
		printf("%s\n", tmp);
	}
	g_globi = 0;
	free(tmp);
}

// affiche une erreur si pwd est use avec des arugument
void	display_pwd_error(t_data *data)
{
	if (data->utils->node->output_fd > 0)
	{
		ft_write_fd("pwd: too many arguments", data->utils->node->output_fd);
	}
	else if (!data->utils->node->output_redirection_error_id)
	{
		printf("pwd: too many arguments");
	}
	g_globi = 1;
}

/*
	OLDPWD stock le chemin du dernier repertoire de travail
	parcour la list des variable d'env et change de repertoire si
	il trouve OLDPWD
	OLDPWD se souvient de ou tu es avant de faire pwd,
	pour y revenir si on fait un cd
*/
void	find_old_pwd(t_env *env, t_data *data)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var_env_name_and_value, \
		ENV_PREVIOUS_WORKING_DIR, 6))
		{
			change_directory_for_oldpwd(env, data);
			break ;
		}
		tmp = tmp->next_var_env_name_and_value;
	}
}
