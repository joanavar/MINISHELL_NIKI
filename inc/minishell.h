/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitadorofeychik <nikitadorofeychik@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:30:01 by camurill          #+#    #+#             */
/*   Updated: 2025/01/30 20:50:14 by nikitadorof      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L

/* ************************************************************************** */
/*                                 INCLUDES                                     */
/* ************************************************************************** */

# include "../Libreries/Libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                 DEFINES                                      */
/* ************************************************************************** */

# define DELIM " \t\r\n\a"

/* Colors */
# define GBD "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

/* Token Types */
# define SPACES 0    // Espacios
# define STRING 1    // String sin comillas
# define STRINGCS 2  // String con comillas simples
# define STRINGCD 3  // String con comillas dobles
# define PIPE 4      // Pipe |
# define HDOC 5      // Heredoc <<
# define REDIROUT 6  // Redirección >
# define APPEND 7    // Append >>
# define REDIRIN 8   // Redirección <

/* ************************************************************************** */
/*                                 STRUCTURES                                   */
/* ************************************************************************** */

extern volatile sig_atomic_t	g_signal_received;

typedef struct s_shell	t_shell;
typedef struct s_export	t_export;

typedef enum e_opcode
{
	CLOSE,
	NO_CLOSE,
	OPEN,
}	t_opcode;

typedef struct s_redir
{
	int				type;
	char			*file_name;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	char						*content;
	int							type;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

typedef struct s_cmd
{
	char						**arr_cmd;
	char						*path;
	int							builtins;
	int							pid;
	int							id;
	int							std_dup;
	int							stdout_dup;
	int							std_in;
	int							std_out;
	int							std_error;
	int							fd_in;
	int							fd_out;
	int							pipe;
	t_redir						*redirs;
	struct s_cmd				*next;
	t_shell						*shell;
}								t_cmd;

typedef struct s_env
{
	char						*value;
	char						*content;
	struct s_env				*next;
	struct s_env				*prev;
}								t_env;

struct s_shell
{
	int							status;
	int							exit_status;
	char						*prompt;
	char						**arg;
	t_env						*env;
	t_export					*export;
	t_token						*eco_token;
	t_cmd						*cmds;
};

/* ************************************************************************** */
/*                              FUNCTION PROTOTYPES                             */
/* ************************************************************************** */

/* Main Functions */
void	init_shell(t_shell **shell, char **env);
int		start_shell(t_shell *shell);
void	clean_data(t_shell *shell);

/* Signal Handlers */
void	check_signal(int signal_received);
void	handle_sigint(int signal);
void	handle_sigint_heredoc(int sig);
void	setup_signal_handlers(void);
void	setup_heredoc_signals(void);
void	restore_signals(void);

/* Built-ins */
int		built_ins(t_cmd *cmd, int type);
void	unset_shell(t_shell *shell, char *arg);
void	get_echo(t_cmd *cmd);
void	get_export(t_cmd *cmd);
void	get_pwd(void);
void	get_cd(t_cmd *cmd);
void	print_env(t_shell *shell);
int		mini_exit(t_cmd *cmd);

/* Heredoc */
t_token	*is_heredoc(t_token *token);

/* Environment */
t_env	*lstnew(char *content);
t_env	*get_env(char **env);
t_env	*choose_env(t_shell *shell);

/* Executor */
int		executor(t_shell *shell);
void	exec_duo(t_cmd *cmd, t_shell *shell);
void	exec_child(t_cmd *cmd, int id, t_shell *shell);
void	exec_parent(t_cmd *cmd, int id, int pid);
void	mini_exec(t_cmd *cmd, t_shell *shell);
char	*get_path(t_cmd *cmd, t_env *env);
void	waiting(t_shell *shell);
t_cmd	*cmds_shell_exec(t_cmd *cmds, t_shell *shell);

/* Pipes */
int		check_pipe(t_cmd **last);
void	ft_dups(t_cmd *cmd);

/* Parser */
t_token	*lectur_imput(char *str, t_env *env);
int		get_token(char *str, t_token **stack);
t_token	*find_last(t_token *stack);
int		is_string(char *str, int i, t_token **stack);
void	remove_quotes(t_token *stack);
int		string_type(t_token *token);
t_cmd	*token_to_cmd(t_token *tokens);
t_token	*space_zero(t_token *token);

/* Redirections */
int		add_redir(t_token *token, t_cmd *cmd);
int		add_first_redir(t_token *token, t_cmd *cmd);
int		add_rest_redir(t_token *token, t_cmd *cmd);
int		heredoc(t_cmd *cmd);
//int		open_file(char *file, int type);
void	check_reddir(t_cmd *cmd);

/* Error Handling */
void	error_message(char *str, t_opcode OPCODE);
void	free_matrix(char **matrix);
void	free_env(t_env *lst);
void	free_token(t_token **lst);
void	free_cmds(t_cmd **cmds);
void	free_redirs(t_redir *redir);
void	free_shell(t_shell **shell);

/* Utils */
int		ft_strcmp(char *src, char *s);
int		check_numeric(char *str);
int		count_cmd(t_cmd *cmd);
int		arr_size(char **array);
void	print_token(t_token **stack);
void	print_line(t_token *tmp);
void	print_cmd(char **array);
void	union_string(t_token *stack);
void	delete_quotes(t_token *token, char *str, int i, int j);
void	delete_expanser(t_token *token, int start, int end);
int		check_specials(char *str, char ltr);
int		count_quotes_utils(t_token *token, int i, int count, char tmp);
int		opcion_syntax(t_token *tmp);
int		change_malloc_token(t_token *str, t_env *env, int measure);

/* Expansor */
void	expandir(t_token **stack, t_env *env);
void	travel_expansor(t_token *token, t_env *env);
void	expander(t_token *token, int i, t_env *env);
t_token	*expansor_res(t_token *tmp);

/* Syntax */
int		syntax_error(t_token **stack);
int		redir_type(t_token *token);
int		opcion_syntax(t_token *tmp);
int		syntax_pipe_or_redi(t_token *token);

#endif
