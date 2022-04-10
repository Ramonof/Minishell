NAME := pipex
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g -c
SRC_DIR := ./srcs/
OBJ_DIR	= ./obj/

SRC_FILES = pipex.c \
			childs.c \
			error.c \
			free.c

BONUS_FILES = child_bonus.c \
				error_bonus.c \
				files_bonus.c \
				free_bonus.c \
				here_doc_bonus.c \
				pipex_bonus.c

FNC_DIR := ./functions/
OBJ_DIR	= ./obj/
BNS_DIR := ./srcs_bonus/
FNC_FILES = ft_split.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strncmp.c

GNL_DIR = ./gnl/
GNL_FILES = get_next_line_utils.c \
			get_next_line.c

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_FILES_F = $(FNC_FILES:.c=.o)
OBJS_FILES_B = $(BONUS_FILES:.c=.o)
OBJ_FILES_GNL = $(GNL_FILES:.c=.o)

OBJ_D_FILES = $(SRC_FILES:.c=.d)
OBJ_D_FILES_F = $(FNC_FILES:.c=.d)
OBJS_B_D = $(BONUS_FILES:.c=.d)
OBJS_GNL_D = $(GNL_FILES:.c=.d)

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
FNC = $(addprefix $(FNC_DIR), $(FNC_FILES))
GNL = $(addprefix $(GNL_DIR), $(GNL_FILES))
BNS = $(addprefix $(BNS_DIR), $(BONUS_FILES))

OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJS_F = $(addprefix $(OBJ_DIR), $(OBJ_FILES_F))
OBJS_GNL = $(addprefix $(OBJ_DIR), $(OBJ_FILES_GNL))
OBJS_B = $(addprefix $(OBJ_DIR), $(OBJS_FILES_B))

OBJS_D = $(addprefix $(OBJ_DIR), $(OBJ_D_FILES))
OBJS_D_F = $(addprefix $(OBJ_DIR), $(OBJ_D_FILES_F))
OBJS_D_B = $(addprefix $(OBJ_DIR), $(OBJS_B_D))
OBJS_D_G = $(addprefix $(OBJ_DIR), $(OBJS_GNL_D))

HEADER := -I includes/
RM := rm -rf

all: $(NAME)

obj: $(SRCS) $(BNS) $(FNC) $(GNL)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(BNS_DIR)%.c
	$(CC) $(CFLAGS) $< -o $@ $(HEADER) -MMD

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $< -o $@ $(HEADER) -MMD

$(OBJ_DIR)%.o: $(FNC_DIR)%.c
	$(CC) $(CFLAGS) $< -o $@ $(HEADER) -MMD

$(OBJ_DIR)%.o: $(GNL_DIR)%.c
	$(CC) $(CFLAGS) $< -o $@ $(HEADER) -MMD

$(NAME): obj $(OBJS) $(OBJS_F) mandatory
	$(CC) $(OBJS_F) $(OBJS) -o $(NAME)

bonus: obj $(OBJS_F) $(OBJS_B) $(OBJS_GNL)
	$(CC) $(OBJS_F) $(OBJS_B) $(OBJS_GNL) -o $(NAME)
	@touch bonus
	@/bin/rm -f mandatory

mandatory:
	@touch mandatory
	@/bin/rm -f bonus

clean:
	$(RM) $(OBJ_DIR)
	/bin/rm -f mandatory
	/bin/rm -f bonus

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

-include $(OBJS_D) $(OBJS_D_F) $(OBJS_D_B) $(OBJS_D_G)

.PHONY: all clean fclean re