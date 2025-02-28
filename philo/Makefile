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
NAME	= philo
CC		= cc
CFLAGS	= -Wextra -Werror -Wall -pthread
HEADERS = -I ./include

SRC_DIR	= philo/
OBJ_DIR = obj/

SRCS	= 	src/philo.c \
			src/utils.c \
			src/error.c \
			src/validation.c \
			src/init.c \
			src/monitor.c \
			src/routines.c \
			src/threads.c

OBJS    = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#----------------------------------------------------------------------------------
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)
		@echo "$(GREEN)Succesfully built philosophers!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $@
#----------------------------------------------------------------------------------
clean:
		@rm	-rf $(OBJ_DIR)

fclean: clean
		@rm -rf $(NAME)
		@echo "$(CYAN)philosophers executable files cleaned$(DEF_COLOR)"

re:	fclean all
		@echo "$(GREEN)Cleaned and rebuilt everytrhing for philosophers$(DEF_COLOR)"
.PHONY: all clean fclean re
