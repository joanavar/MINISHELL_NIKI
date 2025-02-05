/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:30:01 by camurill          #+#    #+#             */
/*   Updated: 2025/02/04 21:02:36 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L

# include "../Libreries/Libft/libft.h"
# include <curses.h> //tgetent-tputs
# include <dirent.h> //opendir-readdir-closedir
# include <fcntl.h>
# include <readline/history.h>  //add_history
# include <readline/readline.h> //readline-rl_replace_line
# include <signal.h>            //signal-signaction-kill
# include <stdio.h>             //printf-perror
# include <stdlib.h>            //malloc-free-getenv
# include <string.h>            //streeror
# include <sys/stat.h>          //stat-lstat-fstat
# include <sys/wait.h>          //wait-waitpid-wait3
# include <term.h>              //tgoto-tgetent
# include <termios.h>           //tcsetattr-tcgetattr-ioctl
# include <unistd.h>            //read-access-fork-execve-unlink-ttyname

# define DELIM " \t\r\n\a"

/***COLORS***/
# define GBD "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BOLD_BLACK "\033[1m\033[30m"
# define BOLD_RED "\033[1m\033[31m"
# define BOLD_GREEN "\033[1m\033[32m"
# define BOLD_YELLOW "\033[1m\033[33m"
# define BOLD_BLUE "\033[1m\033[34m"
# define BOLD_MAGENTA "\033[1m\033[35m"
# define BOLD_CYAN "\033[1m\033[36m"
# define BOLD_WHITE "\033[1m\033[37m"

# define SPACES 0   // 0 = ESPACIOS
# define STRING 1   // 1 = STRING SIN COMILLAS
# define STRINGCS 2 // 2 = STRING CON COMILLAS SIMPLES
# define STRINGCD 3 // 3 = STRING CON COMILLAS DOBLES
# define PIPE 4     //  = PIPE |
# define HDOC 5     //  = HEREDOC <<
# define REDIROUT 6 //  = REDIRECCION >
# define APPEND 7   //  = APEND >>
# define REDIRIN 8  //  = REDIRECCION <
//# define DOLLAR		9 //  = $
/*	STRUCTS		*/
/*	struct with tokens	*/

extern volatile sig_atomic_t	g_signal_received;

typedef struct s_shell			t_shell;

typedef struct s_export			t_export;

typedef enum e_opcode
{
	CLOSE,
	NO_CLOSE,
	OPEN,
}								t_opcode;

typedef struct s_redir
{
	int							type;
	char						*file_name;
	int							fd;
	struct s_redir				*next;
}								t_redir;

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
	char						**trust;

}								t_cmd;

typedef struct s_trust
{
	char						**arg;
}								t_trust;

typedef struct s_env
{
	char						**arr_export;
	char						*value;
	char						*content;
	struct s_env				*next;
	struct s_env				*prev;
}								t_env;

struct							s_shell
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

/***FUNTIONS AUX***/
int								check_specials(char *str, char ltr);
int								check_numeric(char *str);
int								count_cmd(t_cmd *cmd);
void							waiting(t_shell *shell);

/***MAIN***/
void							init_shell(t_shell **shell, char **env);
void							clean_data(t_shell *shell);
int								start_shell(t_shell *shell, t_trust *trust);

/*** LECTUR ***/
t_token							*lectur_imput(char *str, t_env *env,
									t_shell *shell);

/****ERORR FOUND***/
void							error_message(char *str, t_opcode OPCODE);
void							free_matrix(char **matrix);
void							free_env(t_env *lst);
void							free_token(t_token **lst);
void							free_cmds(t_cmd **cmds);
void							free_redirs(t_redir *redir);
void							free_shell(t_shell *shell);

/***SIGNAL***/
void							check_signal(int sisgnal_received);
void							handle_sigint(int signal);
void							handle_sigint_heredoc(int sig);
void							set_heredoc_signals(void);
void							reset_signals(void);
void							signals_init(void);

/***BUILTS_INS***/
void							unset_shell(t_shell *shell, char *arg);
void							get_echo(t_cmd *cmd);
void							get_export(t_cmd *cmd, t_trust *trust);
void							get_pwd(void);
void							get_cd(t_cmd *cmd);
void							print_env(t_shell *shell, t_cmd *cmd);
int								built_ins(t_cmd *cmd, int type, t_trust *trust);
void							res_pwd(char *cwd, t_env *env, char *old_pwd,
									t_shell *shell);

/***Exit***/
int								mini_exit(t_cmd *cmd);

/***ENV ***/
t_env							*lstnew(char *content);
t_env							*get_env(char **env);

/*** EXECUTOR ***/
void							exec_duo(t_cmd *cmd, t_shell *shell,
									t_trust *trust);
char							*get_path(t_cmd *cmd, t_env *env);
void							exec_child(t_cmd *cmd, int id, t_shell *shell,
									t_trust *trust);
void							mini_exec(t_cmd *cmd, t_shell *shell);
int								add_redir(t_token *token, t_cmd *cmd,
									t_shell *shell);
int								add_first_redir(t_token *token, t_cmd *cmd,
									t_shell *shell);
int								add_rest_redir(t_token *token, t_cmd *cmd,
									t_shell *shell);
t_env							*choose_env(t_shell *shell);
t_cmd							*cmds_shell_exec(t_cmd *cmd, t_shell *shell);
t_token							*space_zero(t_token *token);
t_cmd							*token_to_cmd(t_token *tokens, t_shell *shell);
int								res_exec(t_shell *shell, t_trust *trust, int i);
void							res_pipe(t_cmd *aux, t_shell *shell);
int								res_string(char *token, t_token **stack,
									char quote);
void							loop_main(t_shell *shell, t_trust *trust);
int								res_travel(t_token *tmp, t_env *env,
									t_shell *shell);
void							expand_exit_status(t_token *token, int i,
									t_shell *shell);
t_cmd							*res_buffer(t_cmd *buffer, t_cmd *aux, int i);
void							res_token(t_token *token, char *tmp, int *i,
									int *count);

/*** PIPES ***/
int								check_pipe(t_cmd **last);
void							ft_dups(t_cmd *cmd);

/*** REDIRECTS ***/
int								check_reddir(t_cmd *cmd, t_shell *shell);

/*** TOKENS */
int								get_token(char *str, t_token **stack);
t_token							*find_last(t_token *stack);
t_cmd							*create_new_cmd(void);
int								is_string(char *str, int i, t_token **stack);
void							remove_quotes(t_token *stack);
int								string_type(t_token *token);

/*** UTILS ***/
int								ft_strcmp(char *src, char *s);
void							print_token(t_token **stack);
int								change_malloc_token(t_token *str, t_env *env,
									int measure);
void							delete_expanser(t_token *token, int start,
									int end);
void							print_token_after_expansor(t_token *stack);
void							union_string(t_token *stack);
void							delete_quotes(t_token *token, char *str, int i,
									int j);
int								count_quotes_utils(t_token *token, int i,
									int count, char tmp);
void							print_line(t_token *tmp);
int								arr_size(char **array);
int								is_spaces(t_cmd *cmd);
t_trust							*create_new_trust(void);

/*** HEREDOC */

int								heredoc(t_cmd *cmd, t_shell *shell,
									char *delimiter);

/*** SINTAX ERROR */
int								syntax_error(t_token **stack);
int								redir_type(t_token *token);
int								opcion_syntax(t_token *tmp);
int								syntax_pipe_or_redi(t_token *token);

/*** EXPANSOR */
void							expandir(t_token **stack, t_env *env,
									t_shell *shell);
int								executor(t_shell *shell, t_trust *trust);
t_token							*is_heredoc(t_token *token);
t_token							*expansor_res(t_token *tmp);
void							travel_expansor(t_token *token, t_env *env,
									t_shell *shell);
void							expander(t_token *token, int i, t_env *env,
									t_shell *shell);

#endif
