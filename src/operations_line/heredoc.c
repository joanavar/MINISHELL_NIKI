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

/*static char *line_expansion(char *line, t_env *env)
{
    t_token *tmp;
    char    *str;

    tmp = (t_token *)malloc(sizeof(t_token));
    if (!tmp)
        return (NULL);
    tmp->content = ft_strdup(line);
    tmp->type = 1;
    if (!tmp->content)
        return (NULL);
    tmp->next = NULL;
    str = tmp->content;
    //falta acabar en caso de expandir;
}
*/

static void  go_heredoc(t_cmd *cmd, int fd_doc)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
            break ;
        if (ft_strcmp(line, cmd->redirs->file_name))
            break ;
        //line = line_expansion(line, env);
        ft_putstr_fd(line, fd_doc);
        ft_putstr_fd("\n", fd_doc);
    }
    if (line != 0)
        free(line);
}

static void child_heredoc(t_cmd *cmd, int *heredoc)
{
    signal(SIGINT, handle_sigint_heredoc);
    close(heredoc[0]);
    go_heredoc(cmd, heredoc[1]);
    close(heredoc[1]);
    exit(0);
}

static int	parent_heredoc(t_cmd *cmd, int *heredoc)
{
	int	exit_status;

	signal(SIGINT, SIG_IGN);
	wait(&exit_status);
	close(heredoc[1]);
	if (WIFEXITED(exit_status))
	{
		exit_status = WEXITSTATUS(exit_status);
		if (exit_status == 1)
			return (-3);
		else
			cmd->std_in = dup(heredoc[0]);
		close(heredoc[0]);
	}
	//signals_init();
	return (0);
}
int heredoc(t_cmd *cmd)
{
    int pid;
    int heredoc[2];
    int i;

    i = pipe(heredoc);
    if (i == -1)
        exit(1);
    pid = fork();
    if (pid == 0)
        child_heredoc(cmd, heredoc);
    else
        return (parent_heredoc(cmd, heredoc));
    return (0);
}
