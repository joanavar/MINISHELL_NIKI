/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:50:29 by camurill          #+#    #+#             */
/*   Updated: 2024/12/03 20:02:10 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset_shell(t_shell *shell, char *arg)
{
	char	*aux;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!shell->arg[1])
		return ;
	while (shell->env[i])
	{
		aux = ft_strjoin(arg, "=");
		if (!aux)
			return ;
		if (!ft_strncmp(shell->env[i], aux, ft_strlen(aux)))
		{
			free(aux);
			break ;
		}
		free(aux);
		i++;
	}
}

void	get_echo(t_shell *shell)
{
	size_t	i;

	i = 1;
	if (!shell->arg[i])
		printf("\n");
	else if (shell->arg[i] && !strncmp("-n", shell->arg[i], 3))
	{
		if (!shell->arg[2])
			return ;
		i++;
		while (shell->arg[i])
		{
			if (shell->arg[i + 1])
				printf("%s ", shell->arg[i]);
			else
				printf("%s", shell->arg[i]);
			i++;
		}
	}
	else if (shell->arg[i] && strncmp("-n", shell->arg[i], 3))
	{
		while (shell->arg[i])
		{
			if (shell->arg[i + 1])
				printf("%s ", shell->arg[i]);
			else
				printf("%s\n", shell->arg[i]);
			i++;
		}
	}
}

int	built_ins(t_shell *shell) //corregir errores
{
	if (!shell->arg[0] || shell->arg[0] == "\0")
		return (0);
	if (!strncmp("exit", shell->arg[0], 5))
	{
		printf(YELLOW"exit\n"GBD);
		if (shell->arg[1])
		{
			printf("minishell: exit: %s: ", shell->arg[1]);
			printf("numeric argument required\n");
		}
		return (-1);
	}
	if (!strncmp("env", shell->arg[0], 4))
		print_env(shell);
	if (!strncmp("pwd", shell->arg[0], 4))
		get_pwd();
	if (!strncmp("export", shell->arg[0], 7))
		get_export(shell);
	if (!strncmp("unset", shell->arg[0], 7))
		unset_shell(shell, shell->arg[1]);
	if (!strncmp("cd", shell->arg[0], 3))
		get_cd(shell);
	if (!strncmp("echo", shell->arg[0], 5))
		get_echo(shell);
	return (0);
}
