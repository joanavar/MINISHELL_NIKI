/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:31 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/31 19:51:51 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_heredoc_input(char *delimiter, t_shell *shell)
{
	char	*line;
	char	*content;
	char	*tmp;
	char	*trimmed;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("\nwarning: here-document delimited by end-of-file\n");
			free(content);
			return (NULL);
		}
		if (g_signal_received == 130)
		{
			free(content);
			free(line);
			return (NULL);
		}
		trimmed = ft_strtrim(line, " \t");
		free(line);
		if (!trimmed)
		{
			free(content);
			return (NULL);
		}
		printf("trimmed: %s\n", trimmed);
		if (ft_strlen(trimmed) == ft_strlen(delimiter) && 
			ft_strncmp(trimmed, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(trimmed);
			break;
		}
		tmp = content;
		content = ft_strjoin(content, trimmed);
		free(tmp);
		free(trimmed);
		if (!content)
			return (NULL);
		tmp = content;
		content = ft_strjoin(content, "\n");
		free(tmp);
		if (!content)
			return (NULL);
	}
	return (content);
}

int	heredoc(char *delimiter, t_shell *shell)
{
	int		fd[2];
	char	*content;
	pid_t	pid;
	int		status;
	char	*clean_delimiter;

	if (!delimiter || pipe(fd) == -1)
		return (-1);
	clean_delimiter = ft_strtrim(delimiter, " \t");
	if (!clean_delimiter)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		free(clean_delimiter);
		return (-1);
	}
	if (pid == 0)
	{
		set_heredoc_signals();
		close(fd[0]);
		content = get_heredoc_input(clean_delimiter, shell);
		if (!content)
		{
			close(fd[1]);
			free(clean_delimiter);
			if (g_signal_received == 130)
				exit(130);
			exit(1);
		}
		write(fd[1], content, ft_strlen(content));
		free(content);
		close(fd[1]);
		free(clean_delimiter);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) == 130)
	{
		shell->exit_status = 130;
		close(fd[0]);
		free(clean_delimiter);
		reset_signals();
		g_signal_received = 0;  // Resetear la señal
		return (-1);
	}
	free(clean_delimiter);
	reset_signals();
	return (fd[0]);
}
