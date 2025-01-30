/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:25:58 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 17:24:17 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_env(t_env *env)
{
	t_env	*aux;
	int		i;

	i = 0;
	aux = env;
	if (!aux)
		return (0);
	if (!aux->next)
		return (1);
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

static char	**lst_to_chr(t_env **env)
{
	char	**aux;
	char	*prom;
	t_env	*a_env;
	int		i;

	a_env = *env;
	i = count_env(a_env);
	aux = malloc(sizeof(char **) * (i + 1));
	if (!aux)
		return (NULL);
	i = 0;
	while (a_env)
	{
		prom = ft_strjoin(a_env->value, "=");
		aux[i] = ft_strjoin(prom, a_env->content);
		i++;
		a_env = a_env->next;
		free(prom);
	}
	aux[i] = NULL;
	return (aux);
}

void	mini_exec(t_cmd *cmd, t_shell *shell)
{
	char	**env_arr;

	env_arr = lst_to_chr(&(shell->env));
	if (!env_arr)
	{
		error_message("Error with env", NO_CLOSE);
		clean_data(shell);
		exit(1);
	}
	if (execve(cmd->path, cmd->arr_cmd, env_arr) == -1)
	{
		ft_putstr_fd("Minishell: Command not found: ", 2);
		ft_putendl_fd(cmd->arr_cmd[0], 2);
		free_matrix(env_arr);
		clean_data(shell);
		exit(127);
	}
	free_matrix(env_arr);
	exit(2);
}
