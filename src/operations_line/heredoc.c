/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:31 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/01 13:57:11 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void run_heredoc(t_cmd *cmd, char *deli, int heredoc, t_shell *shell)
{
	char	*line;
	
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!strncmp(line, deli, ft_strlen(deli) + 1))
			break;
		ft_putstr_fd(line, heredoc);
		ft_putstr_fd("\n", heredoc);
		free(line);
	}
	if (line != 0)
		free(line);
}

static void	child_heredoc(t_cmd *cmd, char *delimiter, int *heredoc, t_shell *shell)
{
	signal(SIGINT, handle_sigint_heredoc);
	close(heredoc[0]);
	run_heredoc(cmd, delimiter, heredoc[1], shell);
	close(heredoc[1]);
	exit (0);
}

static int	parent_heredoc(t_cmd *cmd, t_shell *shell, int *heredoc)
{
	int exit_status;

	signal(SIGINT, SIG_IGN);
	wait(&exit_status);
	while (WIFEXITED(exit_status))
	{
		exit_status = WEXITSTATUS(exit_status);
		if (exit_status == 1)
			return (-3);
		else
			cmd->std_in = dup(heredoc[0]);
		close(heredoc[0]);
	}
	signals_init();
	return (0);
}

int	heredoc(t_cmd *cmd, t_shell *shell, char *delimiter)
{
	int	pid;
	int	heredoc[2];

	if (pipe(heredoc) == -1)
		exit (1);
	pid = fork();
	if (pid == 0)
		child_heredoc(cmd, delimiter, heredoc, shell);
	else
		return (parent_heredoc(cmd, shell, heredoc));
	return (0);
}
