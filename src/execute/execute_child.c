/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:03:17 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:12:39 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 글로벌구조체에 exitcode로 종료하는 함수
 * 			fd를 닫고, redir/dup2 를 재설정
 *
 * @param infile_fd - 닫을 fd
 * @param outfile_fd - 닫을 fd
 * @param fd_in - 닫아야할 파이프의 Fd
 */
static void	run_exit_close_fd(int infile_fd, int outfile_fd, int fd_in)
{
	if (close(fd_in) == -1)
		exit_erremsg("close failed\n", NULL, NULL, 1);
	reset_redir(infile_fd, outfile_fd);
	exit (get_global_data()->exitcode);
}

/**
 * @brief - fork()를 하고 execve를 실행하거나 빌트인함수를 실행하는 함수
 *
 * @param table - 글로벌 테이블
 * @param fd - 파이프가 있는경우 사용해야하는 fd
 * @param fd_in - infile의 fd
 * @param contains_pipes - 사용할 파이프가 있는지
 */
void	run_child(t_table table, int *fd, int fd_in, t_bool contains_pipes)
{
	int	infile_fd;
	int	outfile_fd;

	signal(SIGINT, SIG_DFL);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit_erremsg("dup2 failed\n", NULL, NULL, 1);
	if (contains_pipes)
	{
		if (close(fd[PIPE_READ_E]) == -1)
			exit_erremsg("close failed\n", NULL, NULL, 1);
		if (dup2(fd[PIPE_WRITE_E], STDOUT_FILENO) == -1)
			exit_erremsg("dup2 failed\n", NULL, NULL, 1);
	}
	if (set_redir((*table.node_head), &infile_fd, &outfile_fd) == -1)
		exit (1);
	set_till_cmd_pipe(table.node_head);
	if (!(*table.node_head))
		run_exit_close_fd(infile_fd, outfile_fd, fd_in);
	else if (run_builtin_child(table))
		run_exit_close_fd(infile_fd, outfile_fd, fd_in);
	execute_cmd((*table.node_head)->arg, (*table.env_head));
	run_exit_close_fd(infile_fd, outfile_fd, fd_in);
}
