/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:48:48 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:14:17 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 이 함수는 file_function을 이용하여 fd를 받는 함수
 *
 * @param file_function fd를 얻는 함수.
 *
 * @param node 노드
 *
 * @param direction 교체될 fd
 *
 * @return - [fd] 파일 디스크립터 dup2'd를 방향 -
 * [-2] file_function에서 받은 파일 fd 없음
 * [-1] 파일 열기 실패
 * [exit] 닫기 / dup2 실패
*/
static int	dup_correct_fd(int (file_function)(t_node *), \
									t_node *node, int direction)
{
	int	fd;

	fd = file_function(node);
	if (fd == -2)
		return (-2);
	else if (fd == -1)
		return (-1);
	if (close(direction) == -1)
		exit_erremsg("close failed\n", NULL, NULL, 1);
	if (dup2(fd, direction) == -1)
		exit_erremsg("dup2 failed\n", NULL, NULL, 1);
	return (fd);
}

/**
 * @brief STDIN, STDOUT을 STDERR로 초기화 하는 함수
 *
 * @param in_fd - 지금 사용하고 있는 STDIN의 fd
 * @param out_fd - 지금 사용하고 있는 STDOUT의 fd
 */
void	reset_redir(int in_fd, int out_fd)
{
	if (in_fd > 0)
	{
		if (close(in_fd) == -1)
			exit_erremsg("close failed\n", NULL, NULL, 1);
		if (close(STDIN_FILENO) == -1)
			exit_erremsg("close failed\n", NULL, NULL, 1);
		if (dup2(STDERR_FILENO, STDIN_FILENO) == -1)
			exit_erremsg("dup2 failed\n", NULL, NULL, 1);
	}
	if (out_fd > 0)
	{
		if (close(out_fd) == -1)
			exit_erremsg("close failed\n", NULL, NULL, 1);
		close(STDOUT_FILENO);
		if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
			exit_erremsg("dup2 failed\n", NULL, NULL, 1);
	}
}

/**
 * @brief STDIN과 STDOUT을 리다이렉션으로 설정하는 함수
 *
 * @param node - node들
 * @param in_fd - 새로운 STDIN이 설정될 값의 포인터
 * @param out_fd - 새로운 STDOUT이 설정될 값의 포인터
 * @return int -
 * 					0 - 성공
 * 					-1 - get_file함수 실패
 * 					exit - close failed / dup2 failed
 */
int	set_redir(t_node *node, int *in_fd, int *out_fd)
{
	*in_fd = dup_correct_fd(get_in_fd, node, STDIN_FILENO);
	if (*in_fd == -1)
		return (-1);
	*out_fd = dup_correct_fd(get_out_fd, node, STDOUT_FILENO);
	if (*out_fd == -1)
	{
		if (*in_fd > 0)
		{
			if (close(*in_fd) == -1)
				exit_erremsg("close failed\n", NULL, NULL, 1);
			if (dup2(STDERR_FILENO, STDIN_FILENO) == -1)
				exit_erremsg("dup2 failed\n", NULL, NULL, 1);
		}
		return (-1);
	}
	return (0);
}
