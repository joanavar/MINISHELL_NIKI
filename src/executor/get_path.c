/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:08:16 by camurill          #+#    #+#             */
/*   Updated: 2025/01/20 14:39:03 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int is_builtins(char *str)
{
	if (str)
	{
		if (ft_strncmp("env", str, ft_strlen(str)))
			return (1);
		if (ft_strncmp("export", str, ft_strlen(str)))
			return (1);
		if (ft_strncmp("unset", str, ft_strlen(str)))
			return (1);
		if (ft_strncmp("pwd", str, ft_strlen(str)))
			return (1);
		if (ft_strncmp("exit", str, ft_strlen(str)))
			return (1);
		if (ft_strncmp("echo", str, ft_strlen(str)))
			return (1);
		if (ft_strncmp("cd", str, ft_strlen(str)))
			return (1);
	}
	return (0);
}
static char *search_path(t_cmd *cmd)
{
	char	*path;

	
	
}

char *get_path(t_cmd *cmd)
{
	char *path;

	if (!cmd->arr_cmd[0] || cmd->arr_cmd[0][0] == '\0')
		return (NULL);
	cmd->builtins = is_builtins(cmd->arr_cmd[0]);
	if (cmd->builtins == 1 && !cmd->next)
		path = ft_strdup(cmd->arr_cmd[0]);
	else
		path = search_path(cmd);
	if (!path)
		error_message("Command not found", NO_CLOSE);
	return (path);
}