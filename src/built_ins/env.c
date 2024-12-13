/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:41:18 by camurill          #+#    #+#             */
/*   Updated: 2024/12/13 18:01:12 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env(t_shell *shell)
{
	t_env	*aux;

	if (shell->eco_token->next != NULL)
	{
		printf(RED"env: ’%s’ No such file or directory\n"GBD, shell->arg[1]);
		return ;
	}
	aux = shell->env;
	while (aux)
	{
		printf("%s=%s\n", aux->value, aux->content);
		aux = aux->next;
	}
}

/*void	unset_shell(t_shell *shell, char *arg)
{
	char	*aux;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!shell->arg[1])
		return ;
	while (shell->env[i])
	{
		aux = ft_strjoin(arg, "=");
		if (!aux)
			return ;
		if (!ft_strncmp(shell->env[i], aux, ft_strlen(aux)))
		{
			free(aux);
			break ;
		}
		free(aux);
		i++;
	}
}*/

void	get_export(t_shell *shell)
{
	t_env	*aux;

	aux = shell->env;
	if (!shell->eco_token->next)
	{
		while (aux)
		{
			printf("declare -x %s=%s\n", aux->value, aux->content);
			aux = aux->next;
		}
	}
	else if (shell->eco_token->next->next)
	{
		if (check_specials(shell->eco_token->next->next->content, '=') == 1)
		{
			while (aux)
				aux = aux->next;
			aux = lstnew(shell->eco_token->next->next->content);//no se adiciona al final de la lista
			if (aux)
				aux->next = NULL;
		}
	}
}
