/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:08:20 by camurill          #+#    #+#             */
/*   Updated: 2024/12/03 20:01:54 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_env(t_shell *shell)
{
	size_t	i;

	i = 0;
	if (shell->arg[1])
	{
		printf(RED"env: ’%s’ No such file or directory\n"GBD, shell->arg[1]);
		return ;
	}
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}

void	get_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}

void	get_cd(t_shell *shell)
{
	if (shell->arg[1] == NULL)
	{
		error_message("Need a relative or absolute path\n", NO_CLOSE);
		return ;
	}
	else if (shell->arg[1])
	{
		if (chdir(shell->arg[1]) != 0)
		{
			perror("cd");
			return ;
		}
	}
	else
	{
		error_message("Too many arguments\n", NO_CLOSE);
		return ;
	}
}

void	get_export(t_shell *shell)
{
	size_t	i;

	i = 0;
	if (shell->arg[1])
	{
		while (shell->arg[i])
			i++;
		if (check_specials(shell->arg[1], '=') == 1)
			shell->env[i] = ft_strdup(shell->arg[1]);
	}
	else
	{
		while (shell->env[i])
		{
			printf("declare -x %s\n", shell->env[i]);
			i++;
		}
	}
}
