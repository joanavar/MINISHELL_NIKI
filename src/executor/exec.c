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

void	print_cmd(char **array)
{
	int i = 0;
	while(array && array[i])
	{
		printf("%s ", array[i]);
		i++;
	}
	printf("\n");
}
void	executor(t_shell *shell)
{
	t_cmd *cmds;
	t_token *tmp;
	cmds = NULL;
	(void)shell;
	tmp = shell->eco_token;
	print_line(tmp);
	cmds = token_to_cmd(tmp);
	//print_cmd(cmds->arr_cmd);
	//if (!cmds)
		//return (0);

	
}

void	exec_ve(t_shell *shell)
{
	(void)shell;
}
