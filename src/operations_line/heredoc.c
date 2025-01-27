/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joanavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:53:31 by joanavar          #+#    #+#             */
/*   Updated: 2025/01/27 14:53:33 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int  go_heredoc(t_cmd *cmd, t_env **env, int fd_doc)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
            break ;
        if (ft_strcmp(line, cmd->file_name))
            break ;
        if (cmd->algo == 'h')// buscar como es la condicion
            line = line_expansion(line, env);
        ft_putstr_fd(line, fd_doc);
        ft_putstr_fd("\n", fd_doc);
    }
    if (line != 0)
        free(line);
}

static child_heredoc(t_cmd cmd, t_env **env, int *heredoc)
{
    //hacer algo de senyales;
    close(heredoc[0]);
    go_heredoc(cmd, env, heredoc[1]);
    close(heredoc[1]);
    exit(0);
}
int heredoc(t_cmd *cmd, t_env **env)
{
    int pid;
    int heredoc[2];
    int i;

    i = pipe(heredoc);
    if (i == -1)
        exit(1);
    pid = fork();
    if (pid == 0)
        child_heredoc(cmd, env, heredoc);
    else
        return (parent_heredoc(cmd, heredoc));
    return (0);
}
