/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:51:10 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 13:32:58 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	aux_export(t_cmd *cmd, t_env *aux)
{
	t_env	*new_node;

	new_node = lstnew(cmd->arr_cmd[1]);
	if (!new_node)
		error_message("Create a new node", CLOSE);
	if (!aux)
	{
		cmd->shell->env = new_node;
		return ;
	}
	while (aux->next)
		aux = aux->next;
	aux->next = new_node;
	new_node->prev = aux;
}

void	get_export(t_cmd *cmd)
{
	t_env	*aux;
	t_env	*new_node;
	int		i;

	if (!cmd || !cmd->shell)
		return ;
	aux = cmd->shell->env;
	if (!cmd->arr_cmd[1])
	{
		while (aux)
		{
			printf("declare -x %s=%s\n", aux->value, aux->content);
			aux = aux->next;
		}
		return ;
	}
	if (check_specials(cmd->arr_cmd[1], '=') == 1)
		aux_export(cmd, aux);
}
