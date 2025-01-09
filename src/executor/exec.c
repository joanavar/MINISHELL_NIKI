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
	
	print_line(tmp);
	//crear pipes
}

void	exec_ve(t_shell *shell)
{
	(void)shell;
}
