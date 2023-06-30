/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:46:21 by gulee             #+#    #+#             */
/*   Updated: 2022/09/12 20:35:58 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 파이프 없이 실행전후에 하는 함수
 *
 * @param node_haeds - node의 head
 * @param list - 환경변수
 * @return 0 - 정상실행
 * @return -1 - 포크실패 / node_head가 없을경우
 * @return exit 127 - 명령어를 못찾음
 */
static int	run_exec_no_pipe(t_node **node_haeds, t_env *list)
{
	int	return_execute;
	int	fork_fd;

	while ((*node_haeds) && (*node_haeds)->type != TOSTDOUT_E)
		del_cmd_node(node_haeds);
	if (!node_haeds)
		return (1);
	fork_fd = fork();
	if (fork_fd == -1)
		return (-1);
	if (fork_fd == 0)
	{
		signal(SIGINT, SIG_DFL);
		return_execute = execute_cmd((*node_haeds)->arg, list);
		if (return_execute == -1)
			exit (1);
		exit (get_global_data()->exitcode);
	}
	save_pid(fork_fd);
	return (0);
}

/**
 * @brief - 파이프 없이 빌트인을 실행하는 함수
 *
 * @param node - 명령리스트의 헤드노드
 * @param list - 환경변수
 * @return 0 - 정상실행
 * @return -1 - 리다이렉션 실패 / 빌트인 실패 / 실행 실패
 */
static int	run_no_pipes(t_node **node, t_env **list)
{
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	if (set_redir(*node, &in_fd, &out_fd) == -1)
		return (-1);
	if (only_builtin(*node))
	{
		if (run_builtin_no_pipe(node, list) == -1)
			return (-1);
	}
	else if (run_exec_no_pipe(node, *list) == -1)
		return (-1);
	reset_redir(in_fd, out_fd);
	return (0);
}

/**
 * @brief - 파이프 내에 모든 명령을 실행하는 함수
 *			기다리지 않고 바로 뒤에 명령 실행
 *
 * @param table - node와 env의 헤더를 가지고 있는 구조체
 * @param fd_in - 입력을 받는 fd
 * @return 0 - 제대로 실행됬을때
 * @return -1 - 닫기 실패 / 포크 실패 / 파이프 실패
 */
static int	run_pipe(t_table table, int fd_in)
{
	const t_bool	has_pipes = is_pipe((*table.node_head));
	int				pipe_fds[2];
	pid_t			fork_pid;

	if (has_pipes && pipe(pipe_fds) == -1)
		return (return_fd_close(get_err(PIPE_ERR_E), fd_in, -1));
	fork_pid = fork();
	if (fork_pid == -1)
	{
		write(STDERR_FILENO, get_err(FORK_ERR_E), \
				ft_strlen(get_err(FORK_ERR_E)));
		if (has_pipes)
			return (close_pipe_fd(pipe_fds, fd_in));
		return (close_pipe_fd(NULL, fd_in));
	}
	else if (fork_pid == 0)
		run_child(table, pipe_fds, fd_in, has_pipes);
	close_fd_run_pipe(has_pipes, fd_in, pipe_fds);
	if (save_pid(fork_pid) == -1)
		return (-1);
	set_next_pipe(table.node_head);
	if (has_pipes == FALSE_E)
		return (0);
	return (run_pipe(table, pipe_fds[PIPE_READ_E]));
}

/**
 * @brief - 실행쪽 메인 함수
 *
 * @param node - 실행할 명령어들의 헤드노드
 * @param list - 환경변수리스트
 * @return 0 - 모든것이 제대로 실행
 * @return -1 - 실행을 시도하다가 실패
 */
int	execute(t_node **node, t_env **list)
{
	int		return_value;
	t_table	table;

	table.node_head = node;
	table.env_head = list;
	signal(SIGINT, exec_sig_handler);
	signal(SIGQUIT, exec_sig_handler);
	if (is_pipe((*table.node_head)))
	{
		return_value = run_pipe(table, STDIN_FILENO);
		if (dup2(STDERR_FILENO, STDIN_FILENO) == -1)
			exit_erremsg("dup2 failed\n", NULL, NULL, 1);
	}
	else
		return_value = run_no_pipes(node, list);
	run_exit_set_code();
	update_pid();
	del_cmd_list(node);
	return (return_value);
}
