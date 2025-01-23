###############################################################################
#                                STANDARDS                                      #
###############################################################################
NAME        =       minishell
RM          =       rm -rf
INCLUDE     =       inc/minishell.h
SRC_DIR     =       src/
OBJ_DIR     =       obj/
LIBFT       =       Libreries/Libft
LIBFT_A     =       $(LIBFT)/libft.a

###############################################################################
#                                COMPILER                                      #
###############################################################################

CC          =       cc
CCFLAGS     =       -g -fsanitize=address -I/usr/local/Cellar/readline/8.2.13/include #-Wall -Wextra -Werror -fsanitize=address
READLINE    =       -L/usr/local/Cellar/readline/8.2.13/lib -lreadline

###############################################################################
#                                    SRC                                        #
###############################################################################

SRC_FILES   =       main/main.c \
                    main/start_shell.c \
                    main/get_env.c \
                    main/clean.c \
                    signal/signal.c \
                    built_ins/cd_pwd.c \
                    built_ins/built_ins.c \
                    built_ins/echo.c \
                    built_ins/env.c \
                    built_ins/utils.c \
					built_ins/export.c \
					built_ins/exit.c \
                    lectur_line/lectur.c \
                    lectur_line/token.c \
                    lectur_line/string.c \
                    operations_line/remove_quotes.c \
                    utils/utils.c \
                    lectur_line/syntax_error.c \
					utils/utils_tokens.c \
                    operations_line/expansor.c \
					executor/exec.c \
					executor/pipe.c \
					executor/get_path.c \
					executor/dups.c \
					executor/mini_exec.c \
					executor/utils.c \
					utils/utils_exec.c \
					executor/token_to_cmd.c

OBJS        =       $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

###############################################################################
#                                RULES                                           #
###############################################################################

all: header $(NAME)

header:
	@echo "\033[35m";
	@echo "############################################################";
	@echo "#                     🚀 COMPILANDO MINISHELL 🚀            #";
	@echo "#----------------------------------------------------------#";
	@echo "# Proyecto: Minishell                                      #";
	@echo "# Autor: [Niki]                                       #";
	@echo "# Fecha: $(shell date '+%Y-%m-%d %H:%M:%S')                #";
	@echo "# ¡Disfruta del viaje al mundo de los shells personalizados! #";
	@echo "############################################################";
	@echo "\033[0m";
	@echo "\033[36m";
	@echo "        \033[1;32m(O_O)\033[0m    ||    \033[1;32m(O_O)\033[0m                   ";
	@echo "       \033[1;33m/ |  | \ \033[0m || \033[1;33m/ |  | \ \033[0m           ";
	@echo "       \033[1;34m| |__| |\033[0m  || \033[1;34m| |__| |\033[0m           ";
	@echo "        \033[1;35m\____/\033[0m   ||  \033[1;35m\____/\033[0m   ";
	@echo
	@echo "        \033[1;32m(O_O)\033[0m    ||    \033[1;32m(O_O)\033[0m                   ";
	@echo "       \033[1;33m/ |  | \ \033[0m || \033[1;33m/ |  | \ \033[0m           ";
	@echo "       \033[1;34m| |__| |\033[0m  || \033[1;34m| |__| |\033[0m           ";
	@echo "        \033[1;35m\____/\033[0m   ||  \033[1;35m\____/\033[0m   ";
	@echo "\033[0m";
	@echo "       \033[1;32mW E L C O M E\033[0m  \033[1;33mT O\033[0m \033[1;34mM I N I S H E L L\033[0m 🌟🔥         ";
	@echo "       🚀 ¡Listo para compilar tu Shell! 🚀                      ";
	@echo "     \033[1;33m💻 Codificando... 📜\033[0m             ";
	@echo "    \033[1;34m🎩 Ejecutando la magia... 🪄\033[0m         ";
	@echo "      \033[1;35m🌟 ¡Listo para compilar! 🖥️\033[0m        ";
	@echo "\033[0m";

$(NAME): $(OBJS) $(LIBFT_A)
	@echo "\033[32m💻 Compiling $(NAME)...\033[0m"
	@$(CC) $(CCFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) $(READLINE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE)
	@echo "\033[33m🔧 Compiling $<...\033[0m"
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -c $< -o $@

$(LIBFT_A):
	@echo "\033[34m📚 Building libft...\033[0m"
	@make -C $(LIBFT) --no-print-directory

clean:
	@echo "\033[31m🧹 Cleaning objects...\033[0m"
	@make -C $(LIBFT) clean --no-print-directory
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "\033[31m🧼 Cleaning binary...\033[0m"
	@make -C $(LIBFT) fclean --no-print-directory
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re