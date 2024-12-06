LIB = ar -rcs
RM = rm -f

CC = gcc
CCFLAGS = -Wall -Wextra -Werror

NAME = libft.a
SRC =	ft_atoi.c ft_strncmp.c ft_memset.c ft_calloc.c ft_strchr.c ft_isalnum.c ft_isalpha.c ft_strrchr.c\
ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
ft_memmove.c ft_bzero.c ft_strdup.c ft_strlcat.c ft_putchar_fd.c \
ft_strlcpy.c ft_strlen.c  ft_strnstr.c  ft_striteri.c ft_putstr_fd.c\
ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c\
ft_strtrim.c ft_itoa.c ft_split.c
OBJ = $(SRC:.c=.o)
INCLUDE = libft.h

BONUSSRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
ft_lstadd_back_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c

BONUSOBJ = $(BONUSSRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	@echo "Libft in system..."
	@$(LIB) $(NAME) $(OBJ)

bonus: $(OBJ) $(BONUSOBJ) $(INCLUDE)
	@$(LIB) $(NAME) $(BONUSOBJ) $(OBJ)

%.o: %.c Makefile libft.h
	@$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	@echo "Libft out system..."
	@$(RM) $(OBJ) $(BONUSOBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus