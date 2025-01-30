/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:42:39 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 16:25:12 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	echo_n(char *content)
{
	int	i;

	if (!content || content[0] != '-')
		return (0);
	if (content[1] != 'n')
		return (0);
	i = 2;
	while (content[i])
	{
		if (content[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	get_echo(t_cmd *cmd)
{
	size_t	i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (!cmd->arr_cmd[1])
	{
		printf("\n");
		return ;
	}
	while (cmd->arr_cmd[i] && echo_n(cmd->arr_cmd[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->arr_cmd[i])
	{
		printf("%s", cmd->arr_cmd[i]);
		if (cmd->arr_cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}
