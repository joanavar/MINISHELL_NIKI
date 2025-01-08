/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:48:01 by camurill          #+#    #+#             */
/*   Updated: 2024/12/14 20:48:40 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	executor(t_shell *shell)
{
	(void)shell;
	int i = 0;
	t_token *tmp = shell->eco_token;

	while (tmp != NULL)
	{
		if (string_type(tmp))
			printf("%s" ,tmp->content);
			//printf("%d: %zu\n", i, ft_strlen(tmp->content));
		else if (tmp->type == 0)
			printf(" ");
		else if (tmp->type == 4)
			printf("|");
		tmp = tmp->next;
		//i++;
	}
	printf("\n");
	
	//crear pipes
}

void	exec_ve(t_shell *shell)
{
	(void)shell;
}
