NAME := minishell
LIBFT := libft/libft.a
CC := gcc
CFLAGS := -Werror -Wall -Wextra -c -lreadline
SRC_DIR := ./srcs/
GNL_DIR := ./gnl/
EXEC_DIR := ./executor/
PARS_DIR := ./parser/
OBJ_DIR	= ./obj/

SRC_FILES = minishell.c \
			error.c \
			init_env.c \
			strcmp.c

GNL_FILES = get_next_line.c \
			get_next_line_utils.c

EXEC_FILES = 	executor.c \
				exec_cmd.c \
				cd.c \
				cd_utils.c \
				export.c \
				export_utils.c \
				handle_unset.c \
				env.c \
				exit.c \
				echo.c \
				pwd.c

PARS_FILES =	parser.c \
				parser_utils.c \
				get_tokens.c \
				expand_tokens.c \
				delete_quotes.c \
				alloc_cmds.c \
				array_operations.c \
				handle_redirects.c \
				syntax_checker.c \
				check_line.c

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_GNL_FILES = $(GNL_FILES:.c=.o)
OBJ_EXEC_FILES = $(EXEC_FILES:.c=.o)
OBJ_PARS_FILES = $(PARS_FILES:.c=.o)

OBJ_D_FILES = $(SRC_FILES:.c=.d)
OBJ_D_GNL_FILES = $(GNL_FILES:.c=.d)
OBJ_D_EXEC_FILES = $(EXEC_FILES:.c=.d)
OBJ_D_PARS_FILES = $(PARS_FILES:.c=.d)

SRCS = 	$(addprefix $(SRC_DIR), $(SRC_FILES)) \
		$(addprefix $(GNL_DIR), $(GNL_FILES)) \
		$(addprefix $(EXEC_DIR), $(EXEC_FILES)) \
		$(addprefix $(PARS_DIR), $(PARS_FILES))

OBJS = 	$(addprefix $(OBJ_DIR), $(OBJ_FILES)) \
		$(addprefix $(OBJ_DIR), $(OBJ_GNL_FILES)) \
		$(addprefix $(OBJ_DIR), $(OBJ_EXEC_FILES)) \
		$(addprefix $(OBJ_DIR), $(OBJ_PARS_FILES))

OBJS_D = 	$(addprefix $(OBJ_DIR), $(OBJ_D_FILES)) \
			$(addprefix $(OBJ_DIR), $(OBJ_D_GNL_FILES)) \
			$(addprefix $(OBJ_DIR), $(OBJ_D_EXEC_FILES)) \
			$(addprefix $(OBJ_DIR), $(OBJ_D_PARS_FILES))

HEADER := -I includes/
RM := rm -rf

all: $(NAME)

obj: $(SRCS)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER) -MMD -lreadline

$(OBJ_DIR)%.o: $(GNL_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER) -MMD -lreadline

$(OBJ_DIR)%.o: $(EXEC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER) -MMD -lreadline

$(OBJ_DIR)%.o: $(PARS_DIR)%.c
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

-include $(OBJS_D)

.PHONY: libft all clean fclean re