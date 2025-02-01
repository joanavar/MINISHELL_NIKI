/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:31 by joanavar          #+#    #+#             */
/*   Updated: 2025/02/01 14:43:15 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include "../../inc/minishell.h"

static void run_heredoc(t_cmd *cmd, char *deli, int heredoc, t_shell *shell)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (strcmp(line, deli) == 0)  // Comparación directa con strcmp
            break;
        ft_putstr_fd(line, heredoc);
        ft_putstr_fd("\n", heredoc);
        free(line);
    }
    if (line)
        free(line);  // Liberar la línea si no es NULL
}

static void child_heredoc(t_cmd *cmd, char *delimiter, int *heredoc, t_shell *shell)
{
    set_heredoc_signals();
    close(heredoc[0]);
    run_heredoc(cmd, delimiter, heredoc[1], shell);
    close(heredoc[1]);
    exit(0);
}

static int parent_heredoc(t_cmd *cmd, t_shell *shell, int *heredoc)
{
    int exit_status;

    signal(SIGINT, SIG_IGN);
    close(heredoc[1]);
    waitpid(-1, &exit_status, 0);

    if (WIFSIGNALED(exit_status) || WEXITSTATUS(exit_status) == 130)
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