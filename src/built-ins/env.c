/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:41:18 by camurill          #+#    #+#             */
/*   Updated: 2024/12/13 17:45:23 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env(t_shell *shell)
{
	size_t	i;

	i = 0;
	if (shell->arg[1])
	{
		printf(RED"env: ’%s’ No such file or directory\n"GBD, shell->arg[1]);
		return ;
	}
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}

void	unset_shell(t_shell *shell, char *arg)
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
}

void	get_export(t_shell *shell)
{
	size_t	i;

	i = 0;
	if (shell->arg[1])
	{
		while (shell->arg[i])
			i++;
		if (check_specials(shell->arg[1], '=') == 1)
			shell->env[i] = ft_strdup(shell->arg[1]);
	}
	else
	{
		while (shell->env[i])
		{
			printf("declare -x %s\n", shell->env[i]);
			i++;
		}
	}
}
