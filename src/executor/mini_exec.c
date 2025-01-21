/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:25:58 by camurill          #+#    #+#             */
/*   Updated: 2025/01/21 21:00:58 by camurill         ###   ########.fr       */
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

static char **lst_to_chr(t_env *env)
{
	char	**aux;
	char	*prom;
	t_env	*a_env;
	int		i;

	i = count_env(env);
	a_env = env;
	aux = malloc(sizeof(char **) * (i + 1));
	if (aux)
		return (NULL);
	i = 0;
	while (a_env)
	{
		prom = ft_strjoin(a_env->value, "=");
		aux[i] = ft_strjoin(prom, a_env->content);
		i++;
		a_env = a_env->next;
	}
	aux[i] = NULL;
	return (aux);
}

void	mini_exec(t_cmd *cmd)
{
	char	**env;

	env = lst_to_chr(cmd->shell->env);
	if (!env)
		error_message("Error with env", NO_CLOSE);
	if (execve(cmd->arr_cmd[0], cmd->arr_cmd, env) == -1)
	{
		ft_putstr_fd("Minishell: Command not found: ", 2);
		ft_putendl_fd(cmd->arr_cmd[0], 2);
	}
	exit(2);
}