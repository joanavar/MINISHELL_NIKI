/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:49:47 by camurill          #+#    #+#             */
/*   Updated: 2025/01/21 15:13:51 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	error_message(char *str, t_opcode OPCODE)
{
	if (OPCODE == NO_CLOSE || OPCODE == CLOSE)
		printf(RED"Error found: %s\n"GBD, str);
	if (OPCODE == CLOSE)
		exit(1);
}

void	init_shell(t_shell **shell, char **env)
{
	(*shell) = malloc(sizeof(t_shell));
	if (!shell || !(*shell))
		error_message("Problems with mallocs", CLOSE);
	(*shell)->prompt = NULL;
	(*shell)->status = 0;
	(*shell)->arg = NULL;
	(*shell)->env = NULL;
	if (!env)
		error_message("Problems, not found env", CLOSE);
	else
		(*shell)->env = get_env(env);
	(*shell)->eco_token = NULL;
}

int	main(int ac, char **ag, char **env)
{
	t_shell	*shell;

	if (ac > 1)
		error_message("Enter only one argument", CLOSE);
	shell = NULL;
	init_shell(&shell, env);
	check_signal(g_signal_received);
	while (1)
	{
		shell->prompt = readline(BLUE"/home/minishell$ "GBD);
		if (!shell->prompt)
		{
			printf("exit\n");
			break ;
		}
		if (*shell->prompt && start_shell(shell) == -1)
			error_message("Syntax Error", NO_CLOSE);
		add_history(shell->prompt);
		free(shell->prompt);
		free_token((shell->eco_token));
		free_cmds((shell->cmds));
	}
	clean_data(shell);
	return (0);
}
