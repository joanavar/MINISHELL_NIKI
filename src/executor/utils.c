/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:40 by camurill          #+#    #+#             */
/*   Updated: 2025/01/21 21:07:49 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_pipe(t_token **tokens, t_cmd **last)
{
	int		fd[2];

	if (!(*tokens) || !(*last))
		return (-1);
	(*last)->pipe = 1;
	if (pipe(fd) == -1)
		return (-1);
	(*last)->fd_out = fd[1];
	(*last)->next->fd_in = fd[0];
	return (0);
}

void	waiting(t_shell *shell)
{
	//Por terminar
}