/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:28:33 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:09:43 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 명령어 개수를 확인하는 함수
 *
 * @param node - 명령어 list
 * @return int 명령어 개수
 */
static int	count_cmd(t_node *node)
{
	int	ret;

	ret = 0;
	while (node != NULL && node->type != PIPE_E)
	{
		if (node->type == TOSTDOUT_E)
			++ret;
		node = node->next;
	}
	return (ret);
}

/**
 * @brief - 다음 파이프로 이동하는 함수
 *
 * @param node - node list
 */
void	next_pipe(t_node **node)
{
	while (*node != NULL && (*node)->type != PIPE_E)
		*node = (*node)->next;
	if (*node != NULL)
		*node = (*node)->next;
}

/**
 * @brief - 합쳐야 할 node를 선택하는 함수
 *
 *
 * @param node - 노드 리스트
 * @param cur_cmd - 파이프 사이에 있는 명령어 개수
 * @return true - 성공
 * @return false - 실패
 */
static t_bool	get_merge_cmd(t_node *node, int cur_cmd)
{
	t_node	*tmp_node;
	t_node	**p_next;

	tmp_node = node;
	while (tmp_node->next != NULL && tmp_node->type != TOSTDOUT_E
		&& tmp_node->type != PIPE_E)
		tmp_node = tmp_node->next;
	node = tmp_node->next;
	p_next = &tmp_node->next;
	while (cur_cmd > 1 && node != NULL)
	{
		if (node->type == TOSTDOUT_E)
		{
			if (merge_cmd(tmp_node, &node, p_next) == FALSE_E)
				return (FALSE_E);
			--cur_cmd;
		}
		else
		{
			p_next = &node->next;
			node = node->next;
		}
	}
	return (TRUE_E);
}

/**
 * @brief - 분리되어 있는 명령어들을 합치는 함수
 *
 * @param node - 작업 목록
 * @return true - 병합에 성공시
 * @return false - 병합에 실패시
 */
t_bool	join_cmds(t_node *node)
{
	int	cur_cmd;

	while (node != 0)
	{
		cur_cmd = count_cmd(node);
		if (get_merge_cmd(node, cur_cmd) == FALSE_E)
			return (bool_err("failed to merge command fragments"));
		next_pipe(&node);
	}
	return (TRUE_E);
}
