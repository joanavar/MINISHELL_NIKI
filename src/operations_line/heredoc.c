/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:31 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/01 15:18:56 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*line_exp(char *line, t_env *env, t_shell *shell)
{
	t_token	*tmp;
	char	*str;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->content = ft_strdup(line);
	if (!tmp->content)
	{
		free(tmp);
		return (NULL);
	}
	tmp->type = 1;
	tmp->next = NULL;
	tmp->prev = NULL;
	expander(tmp, 0, env, shell);
	str = ft_strdup(tmp->content);
	free(tmp->content);
	free(tmp);
	return (str);
}

static void	run_heredoc(int fd, char *delimiter, t_shell *shell)
{
	char	*line;
	char	*expanded;

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
			free(line);
			close(fd);
			exit(0);
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

static void	child_heredoc(int *pipe_fd, char *delimiter, t_shell *shell)
{
	set_heredoc_signals();
	close(pipe_fd[0]);
	run_heredoc(pipe_fd[1], delimiter, shell);
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

int heredoc(t_cmd *cmd, t_shell *shell, char *delimiter)
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
		child_heredoc(pipe_fd, delimiter, shell);

	result = parent_heredoc(cmd, shell, pipe_fd);
	reset_signals();
	return (result);
}
