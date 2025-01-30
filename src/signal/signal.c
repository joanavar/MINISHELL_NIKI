/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:30:19 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 17:28:19 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static struct sigaction	g_old_sigint;
static struct sigaction	g_old_sigquit;
static struct sigaction	g_old_sigpipe;

void	handle_sigint(int signal)
{
	(void)signal;
	g_signal_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		return;
	rl_replace_line("", 0);
	rl_redisplay();
}

void	check_signal(int signal_received)
{
	struct sigaction	sigint;
	struct sigaction	sigout;
	
	(void)signal_received;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_handler = handle_sigint;
	sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
	{
		perror("sigaction error");
		error_message("signation", CLOSE);
	}

	sigemptyset(&sigout.sa_mask);
	sigout.sa_handler = SIG_IGN;
	sigout.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sigout, NULL) == -1)
	{
		perror("sigaction error");
		error_message("signation", CLOSE);
	}
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	restore_signals(void)
{
	if (sigaction(SIGINT, &g_old_sigint, NULL) == -1 ||
		sigaction(SIGQUIT, &g_old_sigquit, NULL) == -1 ||
		sigaction(SIGPIPE, &g_old_sigpipe, NULL) == -1)
		perror("Error restoring signals");
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_pipe;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;

	sa_pipe.sa_handler = SIG_IGN;
	sigemptyset(&sa_pipe.sa_mask);
	sa_pipe.sa_flags = SA_RESTART;

	if (sigaction(SIGINT, &sa_int, &g_old_sigint) == -1 ||
		sigaction(SIGQUIT, &sa_quit, &g_old_sigquit) == -1 ||
		sigaction(SIGPIPE, &sa_pipe, &g_old_sigpipe) == -1)
		error_message("sigaction error", CLOSE);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_message("heredoc signal error", CLOSE);
	signal(SIGQUIT, SIG_IGN);
}



