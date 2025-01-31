/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:31 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/31 18:55:51 by camurill         ###   ########.fr       */
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
			break;
		}
		trimmed = ft_strtrim(line, " \t");
		free(line);  // Liberamos la línea original
		if (!trimmed)
		{
			free(content);
			return (NULL);
		}
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
			exit(1);
		write(fd[1], content, ft_strlen(content));
		free(content);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
	{
		close(fd[0]);
		free(clean_delimiter);
		return (-1);
	}
	free(clean_delimiter);
	return (fd[0]);
}
