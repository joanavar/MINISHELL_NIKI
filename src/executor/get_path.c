/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:08:16 by camurill          #+#    #+#             */
/*   Updated: 2025/01/22 15:39:04 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int is_builtins(char *str)
{
	if (str)
	{
		if (!ft_strncmp("env", str, ft_strlen(str)))
			return (1);
		if (!ft_strncmp("export", str, ft_strlen(str)))
			return (1);
		if (!ft_strncmp("unset", str, ft_strlen(str)))
			return (1);
		if (!ft_strncmp("pwd", str, ft_strlen(str)))
			return (1);
		if (!ft_strncmp("exit", str, ft_strlen(str)))
			return (1);
		if (!ft_strncmp("echo", str, ft_strlen(str)))
			return (1);
		if (!ft_strncmp("cd", str, ft_strlen(str)))
			return (1);
	}
	return (0);
}
static char *get_p_env(t_cmd *cmd, char *str)
{
	t_env	*env;

	env = cmd->shell->env;
	while (env)
	{
		if (!ft_strncmp(env->value, str, ft_strlen(str)))
			return (env->content);
		env = env->next;		
	}
	return (NULL);
}

static char *search_path(t_cmd *cmd)
{
	char	**path;
	char	*path_aux;
	char	*exec;
	int		i;

	path = ft_split(get_p_env(cmd, "PATH"), ':');
	i = -1;
	while(path[++i])
	{
		path_aux = ft_strjoin(path[i], "/");
		if (!path_aux)
			return (free_matrix(path), NULL);
		exec = ft_strjoin(path_aux, cmd->arr_cmd[0]);
		if (!exec)
			return (free_matrix(path), free(path_aux), NULL);
		if (access(exec, F_OK) == 0 && access(exec, X_OK) == 0)
			return (free_matrix(path), free(path_aux), exec);
		free(exec);
		free(path_aux);		
	}
	return (free_matrix(path), cmd->arr_cmd[0]);
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