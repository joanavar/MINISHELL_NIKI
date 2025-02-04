#include "../../inc/minishell.h"

void    res_pwd(char *cwd, t_env *env, char *old_pwd, t_shell *shell)
{
    while (env)
	{
		if (!ft_strncmp(env->value, "OLDPWD", 7))
		{
			free(env->content);
			env->content = old_pwd;
			break ;
		}
		env = env->next;
	}
    if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		env = shell->env;
		while (env)
		{
			if (!ft_strncmp(env->value, "PWD", 4))
			{
				free(env->content);
				env->content = ft_strdup(cwd);
				break ;
			}
			env = env->next;
		}
	}
}

int res_exec(t_shell *shell, t_trust *trust, int i)
{
	if (shell->cmds->path && shell->cmds->builtins == 1
		&& shell->cmds->next == NULL)
		i = built_ins(shell->cmds, 0, trust);
	else
	{
		exec_duo(shell->cmds, shell, trust);
		i = shell->exit_status;
	}
	if (shell->cmds)
		free_cmds(&shell->cmds);
    return (i);
}
void    res_pipe(t_cmd *aux, t_shell *shell)
{
    if (!aux->path)
	{
		if (aux->shell->exit_status == 130)
		{
			clean_data(shell);
			exit(130);
		}
		if (aux->shell->exit_status == 0)
			exit(0);
		ft_putstr_fd("Minishell: Command not found: ", 2);
		ft_putendl_fd(aux->arr_cmd[0], 2);
		clean_data(shell);
		exit(127);
	}
}

int res_string(char *token, t_token **stack, char quote)
{
    if (!get_token(token, stack))
	{
		free(token);
		return (0);
	}
	if (quote == '\'')
		(*stack)->type = 2;
	else
		(*stack)->type = 3;
    return (1);
}

void    loop_main(t_shell *shell, t_trust *trust)
{
    int status;

	while (1)
	{
		shell->prompt = readline(BLUE "/home/minishell$ " GBD);
		if (!shell->prompt)
		{
			printf("exit\n");
			break ;
		}
		status = start_shell(shell, trust);
		if (status == 1)
			break ;
		if (ft_strncmp(shell->prompt, "", ft_strlen(shell->prompt)))
			add_history(shell->prompt);
		free(shell->prompt);
	}
}