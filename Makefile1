NAME        := minishell
CC          := cc
FLAGS       := -Wall -Wextra -Werror
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=  main.c \
                init.c \
                parse.c \
                quote_utils.c \
				dquote_utils.c \
				redirection.c \
                tokens.c \
                env_utils.c \
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
                builtin_commands.c \
                builtin_commands1.c

# Directory for object files
OBJ_DIR     := compiled

# Create a list of object files with the path to the compiled directory
OBJS        := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Create a list of dependency files (.d)
DEPS        := $(OBJS:.o=.d)

# Readline directory (check the path on your system)
READLINE_DIR := /usr/local/opt/readline

# Directory and file for the libft library
LIBFT_DIR   := libft
LIBFT_LIB   := $(LIBFT_DIR)/libft.a

# Additional flags for include directories
INCLUDES    := -I $(LIBFT_DIR)

################################################################################
#                                  Makefile  objs                              #
################################################################################

CLR_RMV     := \033[0m
RED         := \033[1;31m
GREEN       := \033[1;32m
YELLOW      := \033[1;33m
BLUE        := \033[1;34m
CYAN        := \033[1;36m
RM          := rm -f

# Make the 'all' target the first in the Makefile
all: $(NAME)

# Rule for building the main executable file
$(NAME): $(LIBFT_LIB) $(OBJS)
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) -L $(READLINE_DIR)/lib -I $(READLINE_DIR)/include -lreadline
	@echo "$(GREEN)$(NAME) created$(CLR_RMV) ✔️"

# Rule for creating the compiled directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule for compiling object files into the compiled directory
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# Rule for building libft
$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

bonus: all

clean:
	@ $(RM) $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
	@ $(MAKE) -C $(LIBFT_DIR) clean
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)object files ✔️"

fclean: clean
	@ $(RM) $(NAME)
	@ $(MAKE) -C $(LIBFT_DIR) fclean
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re: fclean all

# Include dependency files
-include $(DEPS)

.PHONY: all clean fclean re
