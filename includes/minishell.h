/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:50:21 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:23:32 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <termios.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_check
{
	NULL_E = 1,
	OLD_E = 3
}	t_check;

typedef enum e_pipe
{
	PIPE_READ_E,
	PIPE_WRITE_E
}	t_pipe;

typedef enum e_err_code
{
	DOT_ERR_E,
	TOKEN_ERR_E,
	NL_ERR_E,
	PIPE_ERR_E,
	FORK_ERR_E,
	UNSET_ERR_E,
	EXPORT_ERR_E,
	IDENT_ERR_E,
	AMBIGU_ERR_E
}	t_err_code;

typedef enum e_main_type
{
	INFILE_E,
	APPEND_E,
	HDOC_E,
	TRUNC_E,
	PIPE_E,
	TOSTDOUT_E,
	HDOCSPACE_E,
	HDOCQUOTE_E,
	AMBIGU_E
}	t_main_type;

typedef enum e_bool
{
	FALSE_E,
	TRUE_E
}	t_bool;

typedef enum e_str_type
{
	SPACE_E,
	SINGLE_E,
	DOUBLE_E
}	t_str_type;

typedef struct s_global_data
{
	int		exitcode;
	pid_t	hdoc_pid;
	t_bool	hdoc_break;
}			t_global_data;

typedef struct s_node
{
	t_main_type		type;
	char			**arg;
	struct s_node	*next;
}					t_node;

typedef struct s_ps_list
{
	pid_t				pid;
	struct s_ps_list	*next;
}						t_ps_list;

typedef struct s_env
{
	char			*str;
	t_bool			is_value;
	struct s_env	*next;
}					t_env;

typedef struct s_hdoc
{
	char			*path;
	struct s_hdoc	*next;
}					t_hdoc;

typedef struct s_table
{
	t_node	**node_head;
	t_env	**env_head;
}			t_table;

/* ================================================================
							utils
================================================================= */
/* ft utils */
size_t			ft_strlen(const char *str);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t destsize);
char			*ft_strdup(char *str);
int				ft_atoi(const char *str);
char			**ft_split(const char *str, char c);
char			*ft_itoa(int n);
t_bool			ft_isalnum(int str);
t_bool			ft_isdigit(int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
int				ft_strncmp(const char *str1, const char *str2, size_t size);
void			*ft_calloc(size_t count, size_t size);
char			*ft_substr(char *s, size_t start, size_t len);

/* get global */
char			*get_err(t_err_code code);
t_global_data	*get_global_data(void);

/* uitls error */
t_bool			bool_err(char *errmsg);
void			*null_err(char *errmsg);
void			print_error_str(char *str1, char *str2, char *str3);
void			print_error_str_char(char *str1, char char1, char char2, \
								char *str2);
int				cd_home_path_not_set(void);

/* utils free */
void			del_cmd_list(t_node **node);
void			del_cmd_node(t_node **node);
void			free_double_array(char **array);
t_bool			del_env_false(t_env **env);

/* utils print */
void			print_cmd(t_node *inlst);
void			print_arr(char **toprint);
void			print_env(t_env *print);

/* utils return */
int				return_erremsg(char *str1, const char *str2, \
								char *str3, int return_value);
void			exit_erremsg(char *str1, char *str2, char *str3, \
								int exit_value);
int				return_fd_close(char *error_message, int fd, \
								int return_value);

/* ================================================================
							parser
================================================================= */
/* parser */
t_node			*parser(char *input, t_env *env);

/* parser_utils */
t_bool			is_space(char c);
t_bool			is_operator(char c);
int				str_end(char *str, int index, int n);
int				len_env(char *str, char end);
int				skip_str(char *str, char quote);

/* parser read */
void			read_input(char *str, int *strlen, t_env *env);
int				len_env_str(char *str, char c, int *strlen, t_env *env);
int				exit_status_numblen(int *strlen, int varlen);

/* parser pipe */
t_node			*parser_pipe(char *input, int *index);

/* parser merge */
t_bool			merge_cmd(t_node *dst, t_node **src, t_node **next);

/* parser list */
t_bool			join_cmds(t_node *lst);

/* parser list utils */
void			in_str_out_node(char *dst, char *src, int *index, t_env *env);

/* parser hdoc */
void			read_hdoc(char *str, int *strlen);
void			in_hdoc_out_str(char *dst, char *src, int *index);
int				cpy_hdoc_till_quote(char *dst, char *src, int *index);

/* parser file */
t_node			*set_redir_node(char *input, int *index, int type, t_env *env);
t_node			*init_filenode(int strlen, int type);
void			skip_operator_space(char *input, int *index);
t_node			*parser_file(char *input, int *index, t_env *env);

/* parser expand */
char			*expander(char *input, t_env *env);
int				get_hdoclen(char *input, int *ret);

/* parser expand utils */
void			cpy_char(char *dst, char *src, int *index, int *j);
int				cpy_once(char *dst, char *src, int *index);
void			cpy_space(char *dst, char *src, int *index);

/* parser env */
int				in_env_till_sapce(char *dst, char *src, t_env *env, int *j);
int				in_env_till_quote(char *dst, char *src, t_env *env, int *j);
int				cpy_env_to_str(char *dst, char *src, t_env *env, \
								int varlen);
void			interp_exit_status(char *dst, int *index);

/* parser cmd */
t_node			*parser_cmd(char *input, int *index, t_env *env);
t_node			*space_edge_case(void);
t_node			*arg_malloc_fail(t_node *node, int j);
t_node			*init_cmd(int arrlen);
int				get_cmd_count(char *str);

/* parser ambigu */
t_node			*set_ambigu(char *input, int *index);
t_node			*create_ambigu_node(int size);
t_bool			ambigu_redirect(char *input, int index, t_env *env);
t_bool			check_ambigu(char *input, int index, t_env *env, char c);

/* ================================================================
							lexer
================================================================= */
char			*lexer(char	*input);
void			skip_string(char *str, int *index);
t_bool			in_str(char c, t_bool reset);
t_bool			check_syntax_error(char *str);

/* ================================================================
							redir
================================================================= */
/* redir */
int				set_redir(t_node *node, int *in_fd, int *out_fd);
void			reset_redir(int in_fd, int out_fd);

/* redir outfile */
int				get_out_fd(t_node *node);

/* redir open error */
int				open_error(char *path, int error);

/* heredoc */
int				heredoc(t_node *node, t_hdoc **file_paths, t_env *env);
void			del_hdoc_file(t_hdoc **files);
int				close_fd_free(int fd, char *str1, char *str2, \
								int return_v);

/* heredoc utils */
void			input_to_hdoc(const char *heredoc_path, \
						char *delimiter, int type, t_env *env);
int				expand_hdoc(char **input, int type, t_env *env);

/* heredoc new file */
int				init_hdoc_file(t_node *heredoc_node, t_hdoc **file_paths);

/* heredoc infile */
int				get_in_fd(t_node *node);

/* ================================================================
							env
================================================================= */
/* env init */
t_bool			init_env_list(char **env, t_env **env_head);

/* env init utils */
t_bool			sort_env_list(t_env **env_head);

/* env check */
void			check_env_is_value(t_env *env);
void			check_env_value(t_env *env);

/* env edd */
int				add_env_node(t_env **env, char *str);
int				set_first_node(t_env **head, char *str);

/* env array */
char			**env_list_to_array(t_env *env_list);
int				env_list_size(t_env *env_list);
char			**free_array_till_index(char **array, int index);

/* env get */
t_env			*get_env_node(t_env *list, char *variable);

/* ================================================================
							signal
================================================================= */
void			init_signals(void);
void			hdoc_handler(int sig);
void			exec_sig_handler(int sig);

/* ================================================================
							builtin
================================================================= */
/* cd */
int				cd(char **argument, t_env **env);
char			*create_new_cd_str(char *var, char *pwd);
int				init_new_old(t_env **env);
int				init_empty_old(t_env *oldpwd, t_bool *is_null);
int				set_oldpwd(t_env *oldpwd);
int				cpy_pwd_node(t_env *oldpwd, t_env *pwd_node, t_bool *is_null);
int				chdir_error(char *str, int error);

/* echo */
void			echo(char **args);

/* env */
void			env(t_env *list);

/* exit */
int				count_string(char **str);
void			exit_shell(char **argument, t_bool print);

/* export */
t_bool			add_env_str(t_env *env, char *to_add);
t_bool			check_append_export(char *input);
t_bool			check_str_in_list(char	*input, t_env *env);
int				add_quote_back_equal(char **strings);
void			bubble_sort_env(char **env_strings, int lst_size);
int				export(char **args, t_env **env);

/* pwd */
void			pwd(void);

/* unset */
void			unset(char **arg, t_env **list);
/* ================================================================
							execute
================================================================= */
/* execute */
int				execute(t_node **node, t_env **list);

/* execute utils */
void			set_till_cmd_pipe(t_node **node);
void			set_next_pipe(t_node **node);
t_bool			is_pipe(t_node *node);
t_bool			only_builtin(t_node *node);
char			*cpy_path(char *argument);

/* execute trash */
void			close_fd_run_pipe(t_bool close_pipe, int fd_in, \
								int *pipe_fds);
int				close_pipe_fd(int *pipe_fds, int fd_in);

/* execute pid */
void			run_exit_set_code(void);
void			update_pid(void);
int				save_pid(pid_t new_pid);
t_ps_list		*get_last_pid_node(void);
t_ps_list		*get_first_pid_node(void);

/* execute path */
char			*get_exec_path(char **args, t_env *list);
t_bool			command_found(const char *path);

/* execute cmd */
int				execute_cmd(char **arguments, t_env *list);

/* execute child */
void			run_child(t_table table, int *fd, int fd_in, \
						t_bool contains_pipes);

/* execute builtin */
int				run_builtin_no_pipe(t_node **node, t_env **list);
t_bool			run_builtin_child(t_table table);

#endif
