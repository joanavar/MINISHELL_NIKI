/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:48:04 by camurill          #+#    #+#             */
/*   Updated: 2024/12/03 20:03:29 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	start_shell(t_shell *shell)
{
	if (parssing(&shell) == -1)
		return (-1);
	//shell->arg = ft_split(shell->prompt, ' ');
	shell->eco_token = lectur_imput(shell->prompt);
	return (0);
}
