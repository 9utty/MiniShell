NAME			=	minishell

CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address
#DEBUG			=	-fsanitize=address -fsanitize=leak -g

RLDIR			=	$(shell brew --prefix)
LIBREADLINE		=	$(RLDIR)/opt/readline/lib

INCLUDE_DIRS	=	-I includes -I $(RLDIR)/opt/readline/include
LIB_DIR			=	-L$(LIBREADLINE) -lreadline

PARSER			= parser.c						\
					parser_utils.c				\
					parser_read.c				\
					parser_pipe.c				\
					parser_merge.c				\
					parser_list.c				\
					parser_list_write.c			\
					parser_hdoc.c				\
					parser_file.c				\
					parser_expand.c				\
					parser_expand_utils.c		\
					parser_expand_len.c			\
					parser_env.c				\
					parser_cmd.c				\
					parser_ambigu.c				\

BUILTIN			= cd.c							\
					cd_utils.c					\
					echo.c						\
					env.c						\
					exit.c						\
					exit_utils.c				\
					export.c					\
					export_utils.c				\
					export_add.c				\
					pwd.c						\
					unset.c						\

ENV				= env_init.c					\
					env_init_utils.c			\
					env_get_node.c				\
					env_check.c					\
					env_array.c					\
					env_add.c					\

EXECUTER		= execute.c						\
					execute_utils.c				\
					execute_trash.c				\
					execute_pid.c				\
					execute_path.c				\
					execute_cmd.c				\
					execute_child.c				\
					execute_builtin.c			\

LEXER			= lexer.c						\
					lexer_in_str.c				\
					lexer_error.c				\

SIGNAL			= signal.c						\

REDIR			= redir.c						\
					redir_outfile.c				\
					redir_open_error.c			\
					heredoc.c					\
					heredoc_utils.c				\
					heredoc_new_file.c			\
					heredoc_infile.c			\

UTILS			= ft_atoi.c						\
					ft_calloc.c					\
					ft_isalnum.c				\
					ft_isdigit.c				\
					ft_itoa.c					\
					ft_split.c					\
					ft_strcmp.c					\
					ft_strlcpy.c				\
					ft_strdup.c					\
					ft_strlcat.c				\
					ft_strlen.c					\
					ft_strncmp.c				\
					ft_substr.c					\
					get_global.c				\
					utils_error.c				\
					utils_error_2.c				\
					utils_free.c				\
					utils_print.c				\
					utils_return.c


SRC 			=	$(addprefix src/parser/, $(PARSER))		\
					$(addprefix src/builtin/, $(BUILTIN))	\
					$(addprefix src/env/, $(ENV))			\
					$(addprefix src/execute/, $(EXECUTER))	\
					$(addprefix src/lexer/, $(LEXER))		\
					$(addprefix src/signal/, $(SIGNAL))		\
					$(addprefix src/redir/, $(REDIR))		\
					$(addprefix src/utils/, $(UTILS))		\
					src/main.c

OBJ_DIR			=	obj

OBJ				=	$(addprefix obj/,$(SRC:%.c=%.o)) \



all				:	$(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o	:	%.c
				mkdir -p $(@D)
				$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $^ -o $@

$(NAME)			:	$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) $(INCLUDE_DIRS) $(LIB_DIR) -o $(NAME)

$(OBJ_DIR)		:
				mkdir -p obj

clean			:
				$(RM) obj

fclean			:
				$(RM) obj
				$(RM) $(NAME)

re				:
				$(RM) obj
				$(RM) $(NAME)
				make all

./PHONY			:	all, clean, fclean, re
