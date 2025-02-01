/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 21:16:22 by camurill          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/01 14:46:17 by camurill         ###   ########.fr       */
=======
/*   Updated: 2025/02/01 14:37:24 by nikitadorof      ###   ########.fr       */
>>>>>>> 6be25854f9fabd806e471d867b4ea9c509bac5dc
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
<<<<<<< HEAD
	struct sigaction sa_int;
    struct sigaction sa_quit;

    suppress_output();

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = handle_sigquit;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa_quit, NULL);
}
=======
	suppress_output();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}*/
>>>>>>> 6be25854f9fabd806e471d867b4ea9c509bac5dc
