NAME := minishell
LIBFT := libft/libft.a
CC := gcc
CFLAGS := -Werror -Wall -Wextra -c -lreadline
SRC_DIR := ./srcs/
GNL_DIR := ./gnl/
OBJ_DIR	= ./obj/

SRC_FILES = minishell.c

GNL_FILES = get_next_line.c \
			get_next_line_utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_GNL_FILES = $(GNL_FILES:.c=.o)

OBJ_D_FILES = $(SRC_FILES:.c=.d)
OBJ_D_GNL_FILES = $(GNL_FILES:.c=.d)

SRCS = 	$(addprefix $(SRC_DIR), $(SRC_FILES)) \
		$(addprefix $(GNL_DIR), $(GNL_FILES))

OBJS = 	$(addprefix $(OBJ_DIR), $(OBJ_FILES)) \
		$(addprefix $(OBJ_DIR), $(OBJ_GNL_FILES))

OBJS_D = 	$(addprefix $(OBJ_DIR), $(OBJ_D_FILES)) \
			$(addprefix $(OBJ_DIR), $(OBJ_D_GNL_FILES))

HEADER := -I includes/
RM := rm -rf

all: $(NAME)

obj: $(SRCS)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER) -MMD -lreadline

$(OBJ_DIR)%.o: $(GNL_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER) -MMD -lreadline

$(NAME): obj $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT): libft
	$(MAKE) -C ./libft

libft: ;

bonus: $(NAME)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) clean -C ./libft

fclean: clean
	/bin/rm -f $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

-include $(OBJS_D) $(OBJS_D_B)

.PHONY: libft all clean fclean re