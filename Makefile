# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 11:54:42 by jaimesan          #+#    #+#              #
#    Updated: 2025/01/23 15:04:51 by jaimesan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#CFLAGS----------------------------------------------------------------------------------

CC 	= cc
CFLAGS 	= -Wall -Wextra -Werror -I ./includes
RM	= rm -rf
NOPRINT = --no-print-directory

#COLOURS---------------------------------------------------------------------------------

GREEN := \033[1;32m
RED := \033[1;31m
RESET := \033[0m

#FILES------------------------------------------------------------------------------------

SRCS = ./src/main/main.c ./src/main/init_struct.c ./src/parsing/exec_commands.c \
	./src/builtins/echo.c ./src/builtins/pwd.c ./src/builtins/cd.c \
	./src/builtins/export.c ./src/builtins/history.c ./src/builtins/unset.c \
	./src/builtins/variable_expansion.c ./src/utils/command_utils.c ./src/utils/error.c  \
	./src/environment/print_env.c ./src/environment/dup_env.c ./src/environment/get_full_name.c \
	./src/utils/fd_utils.c ./src/main/handle_signals.c ./src/parsing/tokenize_commands.c \
	./src/utils/parsing_utils.c ./src/utils/count_commands_utils.c \
	./src/parsing/process_commands.c ./src/parsing/quotations_commands.c ./src/utils/cd_utils.c \
	./src/utils/quotations_commands_utils.c ./src/utils/check_path.c ./src/builtins/exit.c \
	./src/utils/cd_oldpwd.c ./src/utils/save_shlvl.c
	

#OBJS--------------------------------------------------------------------------------------

OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

#Make---------------------------------------------------------------------------------------

all: $(NAME)

$(LIBFT):
	@$(MAKE) $(NOPRINT) -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline 
	@echo "[100%] $(GREEN)(Minishell) Compilation  | Minishell | successful!$(RESET)"

clean:
	$(MAKE) $(NOPRINT) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)
	@echo "[100%] $(RED)(Minishell) Cleaning up exept compilers ..$(RESET)"

fclean:
	$(MAKE) $(NOPRINT) fclean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(NAME)
	@echo "[100%] $(RED)(Minishell) Cleaning up...$(RESET)"

re: fclean all bonus

#RULES-------------------------------------------------------------------------------------

.PHONY:	all clean fclean re bonus

.SILENT:
