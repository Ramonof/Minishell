NAME = minitalk
SERVER_NAME = server
CLIENT_NAME = client
INCLUDES = minitalk.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SERVER_FILES = server \
			   minitalk_utils

CLIENT_FILES = client \
			   minitalk_utils

all: $(SERVER_NAME) $(CLIENT_NAME)

SRCS_DIR = ./
SERVER_SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SERVER_FILES)))
CLIENT_SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(CLIENT_FILES)))

OBJS_DIR = ./
SERVER_OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SERVER_FILES)))
CLIENT_OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(CLIENT_FILES)))

$(NAME): all

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(SERVER_NAME): $(SERVER_OBJS) $(INCLUDES)
	$(CC) $(SERVER_OBJS) -o $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS) $(INCLUDES)
	$(CC) $(CLIENT_OBJS) -o $(CLIENT_NAME)

clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
	$(RM) $(SERVER_BONUS_OBJS) $(CLIENT_BONUS_OBJS)

fclean: clean
	$(RM) $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

.PHONY: all clean fclean re
