/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:08:16 by camurill          #+#    #+#             */
/*   Updated: 2025/01/31 12:41:33 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_builtins(char *str)
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

static char	*get_p_env(t_env *old_env, char *str)
{
	t_env	*env;
	char	*tmp;

	env = old_env;
	while (env)
	{
		if (!ft_strncmp(env->value, str, ft_strlen(str)))
		{
			tmp = ft_strdup(env->content);
			if (!tmp)
				return (NULL);
			return (tmp);
		}
		env = env->next;
	}
	return (NULL);
}

static char	*search_path(t_cmd *cmd, t_env *env)
{
	char	**path;
	char	*aux;
	char	*path_aux;
	int		i;

	path = ft_split(get_p_env(env, "PATH"), ':');
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		aux = ft_strjoin(path[i], "/");
		if (!aux)
			return (free_matrix(path), NULL);
		path_aux = ft_strjoin(aux, cmd->arr_cmd[0]);
		free(aux);
		if (!path_aux)
			return (free_matrix(path), NULL);
		if (access(path_aux, F_OK | X_OK) == 0)
			return (free_matrix(path), path_aux);
		free(path_aux);
	}
	free_matrix(path);
	return (NULL);
}

char	*get_path(t_cmd *cmd, t_env *env)
{
	t_cmd	*aux;
	char	*path;

	if (!cmd || !cmd->arr_cmd || cmd->arr_cmd[0][0] == '\0')
		return (NULL);
	aux = cmd;
	while (aux)
	{
		aux->builtins = is_builtins(aux->arr_cmd[0]);
		aux = aux->next;
	}
	if (cmd->builtins == 1 && !cmd->next)
		path = ft_strdup(cmd->arr_cmd[0]);
	else
		path = search_path(cmd, env);
	if (!path)
		return (NULL);
	return (path);
}
