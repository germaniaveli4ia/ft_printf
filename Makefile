NAME		:= libftprintf.a

MAKE 		:= make
PTF_INC		:= -I ./includes

LIBFT		:= ./libft
LIBFT_INC	:= $(LIBFT)/includes
LIBFT_LNK 	:= -L $(LIBFT) -lft

LIBS_INC	:= -I$(LIBFT_INC)
LIBS_LNK	:= $(LIBFT_LNK)

HEADERS_LIST 	= ft_printf.h
HEADERS_DIR 	= ./includes/
HEADERS 	= $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_FILES	:=	handlers/ft_treatcsp.c \
				handlers/ft_treatfloat.c \
				handlers/ft_treatn.c \
				handlers/ft_treatint.c \
				handlers/ft_treatuox.c \
				helpers/ft_prec_numb.c \
				helpers/ft_itoa_double.c \
				ft_specifications.c \
				buffer.c \
				ft_parse.c \
				ft_printf.c
SRC_DIR		:= ./src/
SRC		:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ		:= $(SRC:.c=.o)

# compiler and flags
CC		:= gcc
CFLAGS		:= -Wall -Wextra -Werror

.PHONY: all clean fclean re

%.o:%.c
	@$(CC) $(CFLAGS) $(PTF_INC) $(LIBS_INC) -c $< -o $@

$(NAME): libs $(OBJ)
	@cp libft/libft.a ./$(NAME)
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

all: $(NAME)

clean:
	@$(MAKE) -C $(LIBFT) clean fclean --no-print-directory
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean --no-print-directory

re: fclean all

libs:
	@$(MAKE) -C $(LIBFT) --no-print-directory

relib:
	@$(MAKE) -C $(LIBFT) re --no-print-directory
	@$(MAKE) re --no-print-directory
