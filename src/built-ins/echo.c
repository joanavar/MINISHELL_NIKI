/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:42:39 by camurill          #+#    #+#             */
/*   Updated: 2024/12/13 17:44:57 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
//ToDo
void	get_echo(t_shell *shell)
{
	size_t	i;

	i = 1;
	if (!shell->arg[i])
		printf("\n");
	else if (shell->arg[i] && !strncmp("-n", shell->arg[i], 3))
	{
		if (!shell->arg[2])
			return ;
		i++;
		while (shell->arg[i])
		{
			if (shell->arg[i + 1])
				printf("%s ", shell->arg[i]);
			else
				printf("%s", shell->arg[i]);
			i++;
		}
	}
	else if (shell->arg[i] && strncmp("-n", shell->arg[i], 3))
	{
		while (shell->arg[i])
		{
			if (shell->arg[i + 1])
				printf("%s ", shell->arg[i]);
			else
				printf("%s\n", shell->arg[i]);
			i++;
		}
	}
}
