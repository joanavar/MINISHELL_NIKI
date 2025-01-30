/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:49:47 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 17:28:38 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	error_message(char *str, t_opcode OPCODE)
{
	if (OPCODE == NO_CLOSE || OPCODE == CLOSE)
		printf(RED "Error found: %s\n" GBD, str);
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
	if (!env || !(*env))
	{
		(*shell)->env = choose_env(*shell);
		if (!(*shell)->env)
			error_message("Problems, not found env", CLOSE);
	}
	else
		(*shell)->env = get_env(env);
	(*shell)->eco_token = NULL;
	(*shell)->cmds = NULL;
}

int	main(int ac, char **ag, char **env)
{
	t_shell	*shell;

	if (ac > 1)
		error_message("Enter only one argument", CLOSE);
	shell = NULL;
	setup_signal_handlers();
	init_shell(&shell, env);
	check_signal(g_signal_received);
	while (1)
	{
		shell->prompt = readline(BLUE "/home/minishell$ " GBD);
		if (!shell->prompt)
		{
			printf("exit\n");
			clean_data(shell);
			return (EXIT_SUCCESS);
		}
		if (*shell->prompt && start_shell(shell) == -1)
			break ;
		if (ft_strncmp(shell->prompt, "", ft_strlen(shell->prompt)))
			add_history(shell->prompt);
		free(shell->prompt);
		shell->prompt = NULL;
	}
	restore_signals();
	clean_data(shell);
	return (0);
}
