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
	t_cmd *cmds;
	t_token *tmp;
	cmds = NULL;
	(void)shell;
	tmp = shell->eco_token;
	print_line(tmp);
	cmds = token_to_cmd(tmp);
	//if (!cmds)
	//	return (0);

	
}

void	exec_ve(t_shell *shell)
{
	(void)shell;
}
