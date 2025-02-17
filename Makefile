#colors------------------------------------------------------------------------------
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
#------------------------------------------------------------------------------------
NAME	= philosophers
CC		= cc
CFLAGS	= -Wextra -Werror -Wall -pthread

SRCS	= $(shell find ./examples -iname "*.c")
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "$(GREEN)Succesfully built philosophers!$(DEF_COLOR)"
