NAME        := minishell
CC        := cc
FLAGS    := -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=  main.c \
                init.c \
                parse.c \
                parse_utils.c \
                quote_utils.c \
				dquote_utils.c \
				redirection.c \
                tokens.c \
                env_utils.c \
                env_utils1.c \
                env_array.c \
                heredoc.c \
                heredoc_utils.c \
                utils.c \
                signals.c \
                free_program.c \
                execute.c \
                execute_builtin.c \
                execute_single_command.c \
                execute_pipeline.c \
                execute_pipeline_utils.c \
                builtin_commands.c \
                builtin_commands1.c
                          
OBJS        := $(SRCS:.c=.o)

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

READLINE_DIR := /usr/local/opt/readline

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

all: $(NAME)

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(CLR_RMV)"
	@$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -L$(READLINE_DIR)/lib -I$(READLINE_DIR)/include -lreadline -L$(LIBFT_DIR) -lft
	@echo "$(GREEN)$(NAME) created ✔️"

clean:
	@ ${RM} *.o */*.o */*/*.o
	@ $(MAKE) -C $(LIBFT_DIR) clean
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean: clean
	@ ${RM} ${NAME}
	@ $(MAKE) -C $(LIBFT_DIR) fclean
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re: fclean all

.PHONY: all clean fclean re


