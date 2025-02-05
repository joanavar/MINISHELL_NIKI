/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:49:47 by camurill          #+#    #+#             */
/*   Updated: 2025/02/05 12:50:50 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

static void	free_trust(t_trust *trust)
{
	if (trust)
		free_matrix(trust->arg);
	if (trust)
		free(trust);
	trust = NULL;
}

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
	(*shell)->exit_status = 0;
}

int	main(int ac, char **ag, char **env)
{
	t_shell	*shell;
	t_trust	*trust;

	(void)ag;
	trust = create_new_trust();
	if (ac > 1)
		error_message("Enter only one argument", CLOSE);
	init_shell(&shell, env);
	check_signal();
	loop_main(shell, trust);
	clean_data(shell);
	free_trust(trust);
	return (0);
}
