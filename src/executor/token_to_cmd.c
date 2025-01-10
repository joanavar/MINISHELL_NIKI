#include "../../inc/minishell.h"

static t_cmd   create_new_cmd(void)
{
    t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return (NULL);
	cmd->arr_cmd = NULL;
	cmd->path = NULL;
	cmd->pid = -1;
	//cmd->fd_in = -1;
	//cmd->fd_out = -1;
	//cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

static char **create_arr_cmd(char *token, char **cmd)
{
    cmd = malloc(sizeof(char *) * 2);
    if (cmd)
        return (NULL);
    cmd[0] = ft_strdup(token);
    if (!cmd[0])
        return (NULL);
    cmd[1] = NULL;
    return (cmd);
}

static char ** add_to_array(char *token, char **cmd)
{
    int i;
    char **new_cmd;

    i = -1;
    new_cmd = NULL;
    if (!cmd)
        return (create_arr_cmd(token, cmd));
    new_cmd = malloc(sizeof(char *) * (arr_size(cmd) + 2));
    if (!new_cmd)
        //liberar la array y ponerla a null;
    while (cmd[++i])
        new_cmd[i] = cmd[i];
    new_cmd[i] = ft_strdup(token);
    if (!new_cmd[i])
        //liberamos las dos arrays, la antigua y la nueva;
    new_cmd[++i] = NULL;
    free(cmd);
    return (new_cmd);
}

int clas_token(t_token **token, t_cmd **aux_cmd)
{
    if ((*tokens)->type == 5 || (*tokens)->type == 6
		|| (*tokens)->type == 7 || (*tokens)->type == 8)
    {
        if ()//funcion para rellener la t_redir;
            return (0);
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
        if (!(*aux_cmd)->next);
            return (0);
        *aux_cmd = (*aux_cmd)->next;
    }
    return (1);
}

t_cmd   *token_to_cmd(t_token *tokens)
{
    t_cmd *cmd;
    t_cmd *aux_cmd;

    cmd = create_new_cmd();
    if (!cmd)
        return (NULL);
    aux_cmd = cmd;
    while (tokens)
    {
        while (tokens->type == 0)
            tokens = tokens->next;
        if (!clas_token(&tokens, &aux_cmd))
        {
            //liberar los cmds hechos hasta ahora
            return (NULL);
        }
        while (tokens->type == 0)
            tokens = tokens->next;
        tokens = tokens->next;
    }
    return (cmd);
}