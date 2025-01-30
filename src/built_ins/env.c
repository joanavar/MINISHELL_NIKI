/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:41:18 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 16:37:43 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env(t_shell *shell)
{
	t_env	*aux;

	if (shell->eco_token->next != NULL)
	{
		printf(RED "env: ’%s’ No such file or directory\n" GBD,
			shell->eco_token->content);
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
		return;
	aux = shell->env;
	if (!aux)
		return;
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
			free(del->value);
			free(del->content);
			free(del);
			return ;
		}
		aux = aux->next;
	}
}
