#include "../../inc/minishell.h"

static t_cmd   *create_new_cmd(void)
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
    if (!cmd)
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

    i = 0;
    new_cmd = NULL;
    if (!cmd)
        return (create_arr_cmd(token, cmd));
    new_cmd = malloc(sizeof(char *) * (arr_size(cmd) + 2));
    if (!new_cmd)
        return (free_matrix(cmd), NULL);
    while (cmd[i])
    {
        new_cmd[i] = cmd[i];
        i++;
    }
    new_cmd[i] = ft_strdup(token);
    if (!new_cmd[i])
        return (free_matrix(cmd), free(new_cmd), NULL);
    new_cmd[++i] = NULL;
    free(cmd);
    i = 0;
    while (new_cmd[i])
    {
        printf ("new_cmd :%s\n", new_cmd[i]);
        i++;
    }
    return (new_cmd);
}

static int clas_token(t_token **token, t_cmd **aux_cmd)
{
    if ((*token)->type == 5 || (*token)->type == 6
		|| (*token)->type == 7 || (*token)->type == 8)
    {
        //if ()//funcion para rellener la t_redir;
          //  return (0);
        (*token) = (*token)->next;
        printf("4\n");
    }
    else if (string_type(*token))
    {
        (*aux_cmd)->arr_cmd = add_to_array((*token)->content,
            (*aux_cmd)->arr_cmd);
        //printf("cmd :%s\n", (*aux_cmd)->arr_cmd[0]);
        if (!(*aux_cmd)->arr_cmd)
            return (0);
    }
    else if ((*token)->type == 4)
    {
        (*aux_cmd)->next = create_new_cmd();
        if (!(*aux_cmd)->next)
            return (0);
        print_cmd((*aux_cmd)->arr_cmd);
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