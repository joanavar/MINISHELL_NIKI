/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:31 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/01 14:54:15 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include "../../inc/minishell.h"

static void run_heredoc(t_cmd *cmd, char *deli, int heredoc, t_shell *shell)
{
	char	*line;
	char	*expanded_line;
	
	while (1)
	{
		line = readline("> ");
		if (!line)  // EOF (Ctrl+D)
		{
			ft_putstr_fd("\nwarning: here-document delimited by end-of-file\n", 2);
			close(heredoc);
			break;  // En lugar de exit, usamos break
		}
		if (g_signal_received == 130)  // Ctrl+C
		{
			free(line);
			close(heredoc);
			exit(130);
		}
		if (!strncmp(line, deli, ft_strlen(deli) + 1))
		{
			free(line);
			break;  // En lugar de exit, usamos break
		}
		expanded_line = line_exp(line, shell->env, shell);
		if (expanded_line)
		{
			ft_putstr_fd(expanded_line, heredoc);
			ft_putstr_fd("\n", heredoc);
			free(expanded_line);
		}
		free(line);
	}
}

static void child_heredoc(t_cmd *cmd, char *delimiter, int *heredoc, t_shell *shell)
{
	set_heredoc_signals();  // Volver a usar set_heredoc_signals
	close(heredoc[0]);
	run_heredoc(cmd, delimiter, heredoc[1], shell);
	close(heredoc[1]);
	if (g_signal_received == 130)
		exit(130);
	exit(0);
}

static int parent_heredoc(t_cmd *cmd, t_shell *shell, int *heredoc)
{
    int exit_status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(heredoc[1]);
	
	waitpid(-1, &exit_status, 0);
	if (WIFSIGNALED(exit_status))
	{
		close(heredoc[0]);
		shell->exit_status = 130;
		reset_signals();  // Usar reset_signals en lugar de signals_init
		return (-1);
	}

	if (WEXITSTATUS(exit_status) == 130)
	{
		close(heredoc[0]);
		shell->exit_status = 130;
		reset_signals();
		return (-1);
	}
	
	cmd->std_in = dup(heredoc[0]);
	close(heredoc[0]);
	reset_signals();
	return (0);
}

int heredoc(t_cmd *cmd, t_shell *shell, char *delimiter)
{
    int pid;
    int heredoc[2];

	g_signal_received = 0;
	if (pipe(heredoc) == -1)
		return (-1);
	
	pid = fork();
	if (pid == -1)
	{
		close(heredoc[0]);
		close(heredoc[1]);
		return (-1);
	}
	
	if (pid == 0)
		child_heredoc(cmd, delimiter, heredoc, shell);
	return (parent_heredoc(cmd, shell, heredoc));
}
