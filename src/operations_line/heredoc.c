/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:31 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/31 16:37:14 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_heredoc_input(char *delimiter, t_shell *shell)
{
	char	*line;
	char	*content;
	char	*tmp;

	content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("\nwarning: here-document delimited by end-of-file\n");
			break;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		tmp = content;
		content = ft_strjoin(content, line);
		free(tmp);
		tmp = content;
		content = ft_strjoin(content, "\n");
		free(tmp);
		free(line);
	}
	return (content);
}

int	heredoc(char *delimiter, t_shell *shell)
{
	int		fd[2];
	char	*content;
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		set_heredoc_signals();
		close(fd[0]);
		content = get_heredoc_input(delimiter, shell);
		write(fd[1], content, ft_strlen(content));
		free(content);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(fd[0]);
		shell->exit_status = 130;
		return (-1);
	}
	return (fd[0]);
}
