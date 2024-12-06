/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:49:47 by camurill          #+#    #+#             */
/*   Updated: 2024/12/03 20:02:38 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	error_message(char *str, t_opcode OPCODE)
{
	if (OPCODE == NO_CLOSE || OPCODE == CLOSE)
		printf(RED"Error found: %s\n"GBD, str);
	if (OPCODE == CLOSE)
		exit(1);
}

void	init_shell(t_shell **shell, char **env)
{
	(*shell) = malloc(sizeof(t_shell));
	if (!shell || !(*shell))
		error_message("Problems with mallocs", CLOSE);
	(*shell)->prompt = NULL;
	(*shell)->token = 0;
	(*shell)->status = 0;
	(*shell)->arg = NULL;
	(*shell)->env = NULL;
	(*shell)->aux_env = NULL;
	get_env(shell, env);//toD
}

void	clean_data(t_shell **shell)
{
	if ((*shell)->prompt)
	{
		free((*shell)->prompt);
		(*shell)->prompt = NULL;
	}
	if ((*shell)->env)
		free_matrix((*shell)->env);
	if ((*shell)->arg)
		free_matrix((*shell)->arg);
	if ((*shell)->aux_env)
		free_matrix((*shell)->aux_env);
	free((*shell));
}

void	free_matrix(char **matrix)
{
	size_t	i;

	i = 0;
	if (!matrix || !(*matrix))
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

int	main(int ac, char **ag, char **env)
{
	t_shell	*shell;

	if (ac > 1)
		error_message("Enter only one argument", CLOSE);
	shell = NULL;
	init_shell(&shell, env);
	check_signal(g_signal_received);
	while (1)
	{
		shell->prompt = readline(BLUE"/home/minishell$ "GBD);
		if (!shell->prompt)
		{
			printf("exit\n");
			break ;
		}
		if (start_shell(shell) == -1)
			error_message("Write a double \" o \'", NO_CLOSE);
		//if (built_ins(shell) == -1)
		//	break ;
		add_history(shell->prompt);
		free(shell->prompt);
	}
	clean_data(&shell);
	return (0);
}
