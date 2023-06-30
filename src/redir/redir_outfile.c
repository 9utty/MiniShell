/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:49:54 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:13:55 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief outfile을 해야하는 fd를 가져오는 함수
 *
 * @param node 노드
 * @return int
 * [-1] - 열기 실패
 * [exit] - close failed
 */
int	get_out_fd(t_node *node)
{
	int	fd;

	fd = -2;
	while (node && node->type != PIPE_E)
	{
		if (node->type == TRUNC_E || node->type == APPEND_E)
		{
			if (fd != -2)
			{
				if (close(fd) == -1)
					exit_erremsg("close failed\n", NULL, NULL, 1);
			}
			if (node->type == APPEND_E)
				fd = open(node->arg[0], O_CREAT | O_WRONLY | O_APPEND, 0666);
			else
				fd = open(node->arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (fd == -1)
				return (open_error(node->arg[0], errno));
		}
		node = node->next;
	}
	return (fd);
}
