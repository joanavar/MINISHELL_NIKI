#include "../../inc/minishell.h"

int res_travel(t_token *tmp, t_env *env, t_shell *shell)
{
    int i;

    i = 0;
	while (tmp->content[i])
	{
		if (!tmp->content[i + 1] && tmp->content[i] == '$')
			return (0);
		else if (tmp->content[i] == '$' && tmp->content[i + 1] == '?')
		{
			expand_exit_status(tmp, i, shell);
			continue ;
		}
		else if (tmp->content[i] == '$')
		{
		    expander(tmp, i, env, shell);
			if (!tmp->content[i++])
				break ;
			continue ;
		}
		i++;
		if (!tmp->content)
			break ;
	}
    return (1);
}

t_cmd   *res_buffer(t_cmd *buffer, t_cmd *aux, int i)
{
	aux = buffer->next;
	if (buffer->arr_cmd)
	{
		i = 0;
		while (buffer->arr_cmd[i])
			free(buffer->arr_cmd[i++]);
		free(buffer->arr_cmd);
	}
	if (buffer->path)
		free(buffer->path);
	if (buffer->redirs)
		free_redirs(buffer->redirs);
	if (buffer->std_in != 0)
		close(buffer->std_in);
	if (buffer->std_out != 1)
		close(buffer->std_out);
	if (buffer->std_error != 2)
		close(buffer->std_error);
	if (buffer->fd_in)
		close(buffer->fd_in);
	if (buffer->fd_out)
		close(buffer->fd_out);
	free(buffer);
	buffer = aux;
    return (buffer);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*aux;
	t_redir	*buffer;

	if (!redir)
		return ;
	buffer = redir;
	if (!buffer->next)
	{
		if (buffer->file_name)
			free(buffer->file_name);
		if (buffer->fd > 2)
			close(buffer->fd);
		free(buffer);
		return ;
	}
	while (buffer)
	{
		aux = buffer->next;
		if (buffer->file_name)
			free(buffer->file_name);
		if (buffer->fd > 2)
			close(buffer->fd);
		free(buffer);
		buffer = aux;
	}
}
void    res_token(t_token *token, char *tmp, int *i, int *count)
{
    while (token->content[*i])
		{
			if (token->content[*i] == *tmp)
			{
				(*i)++;
				(*tmp) = 0;
				break ;
			}
			(*i)++;
			(*count)++;
		}
}
