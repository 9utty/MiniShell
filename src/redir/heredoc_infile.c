/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_infile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:52:13 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:19:39 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - error를 처리하는 함수
 *
 * @param error_str - error 메시지
 * @return int - -1
 */
static int	hdoc_ambigu_error(char *error_str)
{
	get_global_data()->exitcode = 1;
	return (return_erremsg("minishell: ", \
		error_str, get_err(AMBIGU_ERR_E), -1));
}

/**
 * @brief - 마지막 fd를 가져오는 함수
 *
 * @param node - 노드의 포인터
 * @return fd - 마지막 infile의 fd번호
 * @return error - 접근 또는 열기 실패
 */
int	get_in_fd(t_node *node)
{
	int	fd;

	fd = -2;
	while (node && node->type != PIPE_E)
	{
		if (node->type == AMBIGU_E)
			return (hdoc_ambigu_error(node->arg[0]));
		if (node->type == INFILE_E || node->type == HDOCSPACE_E
			|| node->type == HDOCQUOTE_E)
		{
			if (fd != -2)
				if (close(fd) == -1)
					exit_erremsg("close failed\n", NULL, NULL, 1);
			fd = open(node->arg[0], O_RDONLY);
			if (fd == -1)
				return (open_error(node->arg[0], errno));
		}
		node = node->next;
	}
	return (fd);
}
