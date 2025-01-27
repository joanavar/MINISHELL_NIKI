#include "../../inc/minishell.h"

t_cmd   *create_new_cmd(void)
{
    t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return (NULL);
	cmd->arr_cmd = NULL;
	cmd->path = NULL;
    cmd->builtins = 0;
    cmd->id = 0;
	cmd->pid = -1;
    cmd->std_in = 0;
    cmd->std_out = 1;
    cmd->std_error = 2;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
    cmd->pipe = 0;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

static char **create_arr_cmd(char *token, char **cmd)
{
    if (!token)
        return (NULL);
    cmd = malloc(sizeof(char *) * 2);
    if (!cmd)
        return (NULL);
    cmd[0] = ft_strdup(token);
    if (!cmd[0])
    {
        free(cmd[0]);
        free(cmd);
        return (NULL);
    }
    cmd[1] = NULL;
    return (cmd);
}

static char ** add_to_array(char *token, char **cmd)
{
    int i;
    char **new_cmd;

    i = 0;
    new_cmd = NULL;
    if (!cmd)
        return (create_arr_cmd(token, cmd));
    new_cmd = malloc(sizeof(char *) * (arr_size(cmd) + 2));
    if (!new_cmd)
        return (free_matrix(cmd), NULL);
    while (cmd[i])
    {
        new_cmd[i] = ft_strdup(cmd[i]);
        if (!new_cmd[i])
            return (free_matrix(new_cmd), NULL);
        i++;
    }
    new_cmd[i] = ft_strdup(token);
    if (!new_cmd[i])
        return (free_matrix(cmd), free_matrix(new_cmd), NULL);
    new_cmd[++i] = NULL;
    free_matrix(cmd);
    return (new_cmd);
}

static int clas_token(t_token **token, t_cmd **aux_cmd)
{
    if ((*token)->type == 5 || (*token)->type == 6
		|| (*token)->type == 7 || (*token)->type == 8)
    {
        if (add_redir(*token, *aux_cmd) == 2)
            return (0);
        while ((*aux_cmd)->redirs)
            (*aux_cmd)->redirs = (*aux_cmd)->redirs->next;
        (*token) = (*token)->next;
        while ((*token)->type == 0)
            (*token) = (*token)->next;
    }
    else if (string_type(*token))
    {
        (*aux_cmd)->arr_cmd = add_to_array((*token)->content,
            (*aux_cmd)->arr_cmd);
        if (!(*aux_cmd)->arr_cmd)
            return (0);
    }
    else if ((*token)->type == 4)
    {
        (*aux_cmd)->next = create_new_cmd();
        if (!(*aux_cmd)->next)
            return (0);
        *aux_cmd = (*aux_cmd)->next;
    }
    return (1);
}

t_cmd   *token_to_cmd(t_token *tokens)
{
    t_cmd   *cmd;
    t_cmd   *aux_cmd;
    t_cmd   *last;
    t_token *tmp;

    tmp = tokens;
    cmd = create_new_cmd();
    if (!cmd)
        return (NULL);
    aux_cmd = cmd;
    while (tokens)
    {
        if (!clas_token(&tokens, &aux_cmd))
        {
            free_cmds(&cmd);
            free_token(&tmp);
            return (NULL);
        }
       // if (check_pipe(&tokens, &aux_cmd) == -1) //Mejorara M ACS
         //   return (NULL); //Crear funcion para limpiar
        tokens = tokens->next;
    }
    if (!cmd)
        return (NULL);
    return (cmd);
}
