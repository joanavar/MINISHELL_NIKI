###############################################################################
#								STANDARS	 								  #
###############################################################################
NAME 		= 		minishell
RM 			= 		rm -rf
INCLUDE		=		inc/minishell.h
SRC_DIR		=		src/
OBJ_DIR		=		obj/
LIBFT		=		Libreries/Libft
LIBFT_A		=		$(LIBFT)/libft.a

###############################################################################
#								COMPILER	  								  #
###############################################################################

CC 			= 		cc
CCFLAGS		= 		-g -fsanitize=address #-Wall -Wextra -Werror -fsanitize=address
READLINE	=		-lreadline

###############################################################################
#									SRC    									  #
###############################################################################

SRC_FILES	=	main.c \
				parssing.c \
				start_shell.c \
				get_env.c \
				signal.c \
				built_ins.c \
				built_ins_aux.c \
				lectur.c \
				token.c \
				string.c \
				remove_quotes.c \
				utils.c \
				syntax_error.c \
				expansor.c

OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

###############################################################################
#								RULES	      								  #
###############################################################################

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CCFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) $(READLINE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE)
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -c $< -o $@

$(LIBFT_A):
	@echo "Building libft..."
	@make -C $(LIBFT) --no-print-directory

clean:
	@echo "Cleaning objects..."
	@make -C $(LIBFT) clean --no-print-directory
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Cleaning binary..."
	@make -C $(LIBFT) fclean --no-print-directory
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
