/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:16:22 by camurill          #+#    #+#             */
/*   Updated: 2025/02/05 12:53:02 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	suppress_output(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= 0001000;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}

void	handle_sigquit(int sig)
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
