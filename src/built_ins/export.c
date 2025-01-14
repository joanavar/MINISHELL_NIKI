/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:51:10 by camurill          #+#    #+#             */
/*   Updated: 2025/01/14 18:47:53 by camurill         ###   ########.fr       */
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
/*static void	aux_export2(t_cmd *cmd, t_env *aux)
{
	void ;
}*/


void	get_export(t_cmd *cmd)
{
	t_env	*aux;
	t_env	*new_node;

	aux = cmd->shell->env;
	if (!cmd->arr_cmd[1])
	{
		while (aux)
		{
			printf("declare -x %s=%s\n", aux->value, aux->content);
			aux = aux->next;
		}
	}
	else if (cmd->arr_cmd[1] && check_specials(cmd->arr_cmd[1], '=') == 1)
		aux_export(cmd, aux);
	//else if (cmd->arr_cmd[1] && !check_specials(cmd->arr_cmd[1], '='))
		//aux_export2(cmd, aux);//ToDo
}
