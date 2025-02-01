/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:16:22 by camurill          #+#    #+#             */
/*   Updated: 2025/02/01 14:37:24 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	suppress_output(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= 0001000;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

/*void	signals_init(void)
{
	suppress_output();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}*/