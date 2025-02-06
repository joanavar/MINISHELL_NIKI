/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:41:18 by camurill          #+#    #+#             */
/*   Updated: 2025/02/06 16:26:21 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_free(t_env *aux)
{
	free(aux->value);
	free(aux->content);
	free(aux);
}

void	print_env(t_shell *shell, t_cmd *cmd)
{
	t_env	*aux;

	if (cmd->arr_cmd[1])
	{
		printf(RED "env: ’%s’ No such file or directory\n" GBD,
			cmd->arr_cmd[1]);
		return ;
	}
	aux = shell->env;
	while (aux)
	{
		printf("%s=%s\n", aux->value, aux->content);
		aux = aux->next;
	}
}

void	unset_shell(t_shell *shell, char *arg)
{
	t_env	*aux;
	t_env	*del;

	if (!shell || !arg)
		return ;
	aux = shell->env;
	if (!aux)
		return ;
	while (aux)
	{
		if (!ft_strncmp(aux->value, arg, ft_strlen(arg) + 1))
		{
			del = aux;
			if (del->next)
				del->next->prev = del->prev;
			if (del->prev)
				del->prev->next = del->next;
			else
				shell->env = del->next;
			ft_free(del);
			return ;
		}
		aux = aux->next;
	}
}
