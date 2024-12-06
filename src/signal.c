/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:30:19 by camurill          #+#    #+#             */
/*   Updated: 2024/12/03 20:03:16 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint(int signal)
{
	(void)signal;
	g_signal_received = 1;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	check_signal(int signal_received)
{
	struct sigaction	sigint;
	struct sigaction	sigout;

	sigint.sa_handler = handle_sigint;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
		error_message("signation", CLOSE);
	sigout.sa_handler = SIG_IGN;
	sigemptyset(&sigout.sa_mask);
	sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sigout, NULL) == -1)
		error_message("signation", CLOSE);
}
