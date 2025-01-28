/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:30:01 by camurill          #+#    #+#             */
/*   Updated: 2025/01/27 17:15:53 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L

# include <stdio.h> //printf-perror
# include <stdlib.h> //malloc-free-getenv
# include <string.h> //streeror
# include <unistd.h> //read-access-fork-execve-unlink-ttyname
# include <dirent.h> //opendir-readdir-closedir
# include <signal.h> //signal-signaction-kill
# include <sys/wait.h> //wait-waitpid-wait3
# include <termios.h> //tcsetattr-tcgetattr-ioctl
# include <sys/stat.h> //stat-lstat-fstat
# include <readline/readline.h> //readline-rl_replace_line
# include <readline/history.h> //add_history
# include <curses.h> //tgetent-tputs
# include <term.h> //tgoto-tgetent
# include <fcntl.h>
# include "../Libreries/Libft/libft.h"

#define DELIM		" \t\r\n\a"

/***COLORS***/
# define GBD	     "\033[0m"
# define BLACK       "\033[30m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"
# define BOLD_BLACK  "\033[1m\033[30m"
# define BOLD_RED    "\033[1m\033[31m"
# define BOLD_GREEN  "\033[1m\033[32m"
# define BOLD_YELLOW "\033[1m\033[33m"
# define BOLD_BLUE   "\033[1m\033[34m"
# define BOLD_MAGENTA "\033[1m\033[35m"
# define BOLD_CYAN   "\033[1m\033[36m"
# define BOLD_WHITE  "\033[1m\033[37m"

# define SPACES		0 // 0 = ESPACIOS
# define STRING 	1  // 1 = STRING SIN COMILLAS
# define STRINGCS	2 // 2 = STRING CON COMILLAS SIMPLES
# define STRINGCD	3 // 3 = STRING CON COMILLAS DOBLES
# define PIPE 		4 //  = PIPE |
# define HDOC		5 //  = HEREDOC <<
# define REDIROUT	6 //  = REDIRECCION >
# define APPEND		7 //  = APEND >>
# define REDIRIN	8 //  = REDIRECCION <
//# define DOLLAR		9 //  = $
/*	STRUCTS		*/
/*	struct with tokens	*/

extern volatile sig_atomic_t	g_signal_received;

typedef struct s_shell	t_shell;

typedef struct s_export t_export;

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
	//int				amb_red;
	struct s_redir	*next;
}	t_redir;


typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			**arr_cmd;
	char			*path;
	int				builtins;
	int				pid;
	int				id;
	int				std_dup;
	int				stdout_dup;
	int				std_in;
	int				std_out;
	int				std_error;
	int				fd_in;
	int				fd_out;
	int				pipe;
	t_redir			*redirs;
	struct s_cmd	*next;
	t_shell			*shell;
}				t_cmd;

typedef struct s_env
{
	char			*value;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;


struct s_shell
{
	int			status;
	int			exit_status;
	char		*prompt;
	char		**arg;
	t_env		*env;
	t_export	*export;
	t_token		*eco_token;
	t_cmd		*cmds;
} ;

/***FUNTIONS AUX***/
/*int		check_doubles(char *str, char ltr);*/
int		check_specials(char *str, char ltr);
int		check_numeric(char *str);
int		count_cmd(t_cmd *cmd);
void	waiting(t_shell *shell);
void 	printf_dups(t_cmd *cmd);
/*
int		parssing(t_shell **shell);
t_env	*get_env(char **env);*/
//void	get_less_env(t_shell *shell, char *cmp);
//void	prints(void);

/***MAIN***/
void	init_shell(t_shell **shell, char **env);
void	clean_data(t_shell *shell);
int		start_shell(t_shell	*shell);

/****ERORR FOUND***/
void	error_message(char *str, t_opcode OPCODE);
void	free_matrix(char **matrix);
void	free_env(t_env *lst);
void	free_token(t_token **lst);
void	free_cmds(t_cmd **cmds);
void    free_redirs(t_redir *redir);
void    free_shell(t_shell *shell);




/***SIGNAL***/
void	check_signal(int sisgnal_received);
void	handle_sigint(int signal);
void	handle_sigint_heredoc(int sig);

//void	handle_sigquit(int signal); quitar

/***BUILTS_INS***/
void	unset_shell(t_shell *shell, char *arg);
void	get_echo(t_cmd *cmd);
void	get_export(t_cmd *cmd);
void	get_pwd(void);
void	get_cd(t_cmd *cmd);
void	print_env(t_shell *shell);
int		built_ins(t_cmd *cmd);
/***Exit***/
int		mini_exit(t_cmd *cmd);

/***ENV ***/
t_env	*lstnew(char *content);
t_env	*get_env(char **env);

/*** EXECUTOR ***/
void	exec_duo(t_cmd *cmd, t_shell *shell);
char	*get_path(t_cmd *cmd, t_env *env);
void	exec_child(t_cmd *cmd, int id, t_shell *shell);
void	mini_exec(t_cmd *cmd, t_shell *shell);

/*** PIPES ***/
int		check_pipe(t_cmd **last);
void	ft_dups(t_cmd *cmd);


/***NAVARRO_FUNCTIONS***/
//lectur.c
t_token	*lectur_imput(char *str, t_env *env);

//token.c
void	get_token(char *str, t_token **stack);
t_token	*find_last(t_token *stack);
t_cmd   *create_new_cmd(void);
//string.c
int		is_string(char *str, int i, t_token **stack);
//remove_quotes.c
void	remove_quotes(t_token *stack);
int		string_type(t_token *token);
//utils.c
int		ft_strcmp(char *src, char *s);
void	print_token(t_token **stack);
int		change_malloc_token(t_token *str, t_env *env, int measure);
void 	delete_expanser(t_token *token, int start, int end);
void	print_token_after_expansor(t_token *stack);
void	union_string(t_token *stack);
void	delete_quotes(t_token *token, char *str, int i, int j);
int 	count_quotes_utils(t_token *token, int i, int count, char tmp);
void	print_line(t_token *tmp);
int arr_size(char **array);
int is_spaces(t_cmd *cmd);


//exec
t_cmd   *token_to_cmd(t_token *tokens);
void	print_cmd(char **array);
int add_redir(t_token *token, t_cmd *cmd);
t_token *space_zero(t_token *token);
int add_first_redir(t_token *token, t_cmd *cmd);
int add_rest_redir(t_token *token, t_cmd *cmd);
t_env   *choose_env(t_shell *shell);

//heredoc

int heredoc(t_cmd *cmd);












//syntax_error.c
int		syntax_error(t_token **stack);
int		redir_type(t_token *token);
int		opcion_syntax(t_token *tmp);
int	syntax_pipe_or_redi(t_token *token);

// expasor.c
//int		close_expansor(t_token *token, int i);
//int		correct_expansor(t_token *token, int i);
//void	expander(t_token *token, int i, t_env **env);
void	expandir(t_token **stack, t_env *env);
int		executor(t_shell *shell);
int	open_file(char *file, int type);
t_token	*is_heredoc(t_token *token);


#endif
