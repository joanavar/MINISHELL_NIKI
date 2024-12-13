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
	t_env	*aux;

	if (shell->eco_token->next != NULL)
	{
		printf(RED"env: ’%s’ No such file or directory\n"GBD, shell->arg[1]);
		return ;
	}
	aux = shell->env;
	while (aux)
	{
		printf("%s=%s\n", aux->value, aux->content);
		aux = aux->next;
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
	if (shell->eco_token->next == NULL)
	{
		error_message("Need a relative or absolute path\n", NO_CLOSE);
		return ;
	}
	else if (shell->eco_token->next->next->content)
	{
		if (chdir(shell->eco_token->next->next->content) != 0)
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
	t_env	*aux;

	aux = shell->env;
	if (!shell->eco_token->next)
	{
		while (aux)
		{
			printf("declare -x %s=%s\n", aux->value, aux->content);
			aux = aux->next;
		}
	}
	else if (shell->eco_token->next->next)
	{
		if (check_specials(shell->eco_token->next->next->content, '=') == 1)
		{
			while (aux)
				aux = aux->next;
			aux = lstnew(shell->eco_token->next->next->content);//no se adiciona al final de la lista
			if (aux)
				aux->next = NULL;
		}
	}
}
