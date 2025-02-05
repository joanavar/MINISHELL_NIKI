/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:31 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/05 13:07:47 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	run_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_signal_received == 130)
		{
			if (line)
				free(line);
			close(fd);
			exit(130);
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			printf("exiting heredoc \n");
			free(line);
			close(fd);
			exit(0);
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

static void	child_heredoc(int *pipe_fd, char *delimiter)
{
	set_heredoc_signals();
	close(pipe_fd[0]);
	run_heredoc(pipe_fd[1], delimiter);
}

static int	parent_heredoc(t_cmd *cmd, t_shell *shell, int *pipe_fd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(pipe_fd[1]);
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) == 130)
	{
		close(pipe_fd[0]);
		shell->exit_status = 130;
		g_signal_received = 130;
		return (-1);
	}
	if (cmd->std_in != 0)
		close(cmd->std_in);
	cmd->std_in = pipe_fd[0];
	return (0);
}

int	heredoc(t_cmd *cmd, t_shell *shell, char *delimiter)
{
	int	pipe_fd[2];
	int	pid;
	int	result;

	if (pipe(pipe_fd) == -1)
		return (-1);
	g_signal_received = 0;
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
		child_heredoc(pipe_fd, delimiter);
	result = parent_heredoc(cmd, shell, pipe_fd);
	reset_signals();
	return (result);
}
