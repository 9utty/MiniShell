/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_trash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:06:38 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:03:38 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 파이프와 열려있는 fd를 종료하는 함수
 *
 * @param pipe_fd - fd를 포함하는 파이프
 * @param fd_in - infile로 사용하는 fd
 * @return -1
 */
int	close_pipe_fd(int *pipe_fd, int fd_in)
{
	if (pipe_fd)
	{
		if (close(pipe_fd[0]) == -1)
			exit_erremsg("close failed\n", NULL, NULL, 1);
		if (close(pipe_fd[1]) == -1)
			exit_erremsg("close failed\n", NULL, NULL, 1);
	}
	if (close(fd_in) == -1)
		exit_erremsg("close failed\n", NULL, NULL, 1);
	return (-1);
}

/**
 * @brief - 열려있는 fd를 종료하는 함수
 *			종료에 실패하면 프로세스 종료
 * @param close_pipe - true로 설정하면 write가 닫힌다
 *
 * @param fd_in - 0보다 크면 fd 종료 실행
 */
void	close_fd_run_pipe(t_bool close_pipe, int fd_in, int *pipe_fd)
{
	if (fd_in > 0)
	{
		if (close(fd_in) == -1)
			exit_erremsg("close failed\n", NULL, NULL, 1);
	}
	if (close_pipe && close(pipe_fd[PIPE_WRITE_E]) == -1)
		exit_erremsg("close failed\n", NULL, NULL, 1);
}
