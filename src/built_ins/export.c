/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:51:10 by camurill          #+#    #+#             */
/*   Updated: 2025/01/28 15:33:50 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	aux_export(t_cmd *cmd, t_env *aux)
{
	t_env	*new_node;

	new_node = lstnew(cmd->arr_cmd[1]);
	if (!new_node)
		error_message("Create a new node", CLOSE);
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new_node;
		aux = new_node->prev;
	}
}

static char	**create_arr_trust(char *s, char **trust)
{
	if (!s)
		return (NULL);
	trust = malloc(sizeof(char *) * 2);
	if (!trust)
		return(NULL);
	trust[0] = ft_strdup(s);
	if (!trust[0])
	{
		free(trust[0]);
		free(trust);
		return (NULL);
	}
	trust[1] = NULL;
	return (trust); 
}

static char	**aux_trust(char *s, char **trust)
{
	char	**new_trust;
	int		i;

	i = 0;
	if (!trust)
		return(create_arr_trust(s, trust));
	new_trust = malloc(sizeof(char *) * (arr_size(trust) + 2));
	if (!new_trust)
		return (free_matrix(new_trust), NULL);
	while (trust[i])
	{
		new_trust[i] = ft_strdup(trust[i]);
		if (!new_trust[i])
			return (free_matrix(new_trust), NULL);
		i++;
	}
	new_trust[i] = ft_strdup(s);
	if (!new_trust[i])
		return (free_matrix(trust), free_matrix(new_trust), NULL);
	new_trust[++i] = NULL;
	free(trust);
	return (new_trust);
}

void	get_export(t_cmd *cmd)
{
	t_env	*aux;
	t_env	*new_node;
	int		i;
	int		j;
	char	**trust;

	aux = cmd->shell->env;
	trust = cmd->shell->trust;
	i = -1;
	if (!cmd->arr_cmd[1])
	{
		while (aux)
		{
			printf("declare -x %s=%s\n", aux->value, aux->content);
			aux = aux->next;
		}
		if (!trust)
			printf("hola\n");
		if (trust)
		{
			j = 0;
			while(trust)
			{
				printf("declare -x %s\n", trust[j]);
				j++;
			}
		}
	}
	else if (cmd->arr_cmd[1] && check_specials(cmd->arr_cmd[1], '=') == 1)
		aux_export(cmd, aux);
	else if (cmd->arr_cmd[1] && check_specials(cmd->arr_cmd[1], '=') == 0)
	{
		trust = aux_trust(cmd->arr_cmd[1], trust);
		printf("Este es mi nuevo export: %s\n", trust[0]);
	}
}
