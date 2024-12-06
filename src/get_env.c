/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:43:52 by camurill          #+#    #+#             */
/*   Updated: 2024/12/03 20:02:22 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_env(t_shell **shell, char **env)
{
	size_t	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		i++;
	(*shell)->env = malloc(sizeof(char **) * (i + 1));
	if (!(*shell)->env)
		error_message("Malloc", CLOSE);
	(*shell)->aux_env = malloc(sizeof(char **) * (i + 1));
	if (!(*shell)->aux_env)
		error_message("Malloc", CLOSE);
	i = 0;
	while (env[i])
	{
		(*shell)->aux_env[i] = ft_strdup(env[i]);
		(*shell)->env[i] = ft_strdup(env[i]);
		i++;
	}
	(*shell)->env[i] = NULL;
}

/*void	get_less_env(t_shell *shell, char *cmp)  Rehacer
{
	size_t	i;
	size_t	j;

	i = 0;
	free_matrix(shell->env);
	//shell->env = NULL;
	while (shell->aux_env[i])
		i++;
	shell->env = malloc(sizeof(char **) * (i));
	if (!shell->env)
		error_message("Malloc", CLOSE);
	i = 0;
	j = 0;
	printf("1\n");
	while (shell->aux_env[i])
	{
		if (!strncmp(shell->aux_env[i], cmp, ft_strlen(cmp)))
			i++;
		//shell->env[j] = ft_strdup(shell->aux_env[i]);
		i++;
		j++;
	}
	//printf("%li\n %li\n",i , j);
	shell->aux_env = shell->env;
}*/
