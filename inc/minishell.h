/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:30:01 by camurill          #+#    #+#             */
/*   Updated: 2024/12/03 18:16:20 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef enum e_opcode
{
	CLOSE,
	NO_CLOSE,
	OPEN,
}	t_opcode;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_shell
{
	int		token;
	int		status;
	char	*prompt;
	char	**arg;
	char	**env;
	char	**aux_env; //quitar
	t_token	*eco_token;
}			t_shell;

/***FUNTIONS***/
int		check_doubles(char *str, char ltr);
int		check_specials(char *str, char ltr);
int		parssing(t_shell **shell);
void	get_env(t_shell **shell, char **env);
void	get_less_env(t_shell *shell, char *cmp);
//void	prints(void);

/***MAIN***/
void	init_shell(t_shell **shell, char **env);
void	clean_data(t_shell **shell);
int		start_shell(t_shell	*shell);

/****ERORR FOUND***/
void	error_message(char *str, t_opcode OPCODE);
void	free_matrix(char **matrix);

/***SIGNAL***/
void	check_signal(int signal_received);
void	handle_sigint(int signal);
//void	handle_sigquit(int signal); quitar

/***BUILTS_INS***/
void	unset_shell(t_shell *shell, char *arg);
void	get_echo(t_shell *shell);
void	get_export(t_shell *shell);
void	get_pwd(void);
void	get_cd(t_shell *shell);
void	print_env(t_shell *shell);
int		built_ins(t_shell *shell);

/***NAVARRO_FUNCTIONS***/
//lectur.c
t_token	*lectur_imput(char *str);

//token.c
void	get_token(char *str, t_token **stack);
t_token	*find_last(t_token *stack);
//string.c
int		is_string(char *str, int i, t_token **stack);
//remove_quotes.c
void	remove_quotes(t_token *stack);
int		string_type(t_token *token);
//utils.c
int		ft_strcmp(const char *src, char *s);
void	print_token(t_token *stack);
//syntax_error.c
int		syntax_error(t_token **stack);
int		redir_type(t_token *token);
// expasor.c
int		close_expansor(t_token *token, int i);
int		correct_expansor(t_token *token, int i);
void	$(t_token *token, int i);
void	expandir(t_token **stack);

#endif
