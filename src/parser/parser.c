/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:25:23 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:26:14 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief 현재 이 프로그램에서 pipi or file, cmd를 만들어야하는지
 * 결정하는 함수
 *
 * @param input 입력한 문자열
 * @param index 문자열 반복을 위한 인덱스
 * @param env 환경 변수 리스트
 * @return t_node* 해당 타입의 위치에 노드를 만든다
 */
static t_node	*selec_type(char *input, int *index, t_env *env)
{
	if (input[*index] == '|')
		return (parser_pipe(input, index));
	if (input[*index] == '<' || input[*index] == '>')
		return (parser_file(input, index, env));
	return (parser_cmd(input, index, env));
}

/**
 * @brief 문자열을 프리하는 함수
 *
 * @param remove 해제해야하는 문자열
 */
static void	free_str(char **remove)
{
	int	index;

	index = 0;
	while (remove[index])
	{
		free(remove[index]);
		++index;
	}
	free(remove);
}

/**
 * @brief node가 잘못된 경우 노드 해제하는 함수
 *
 * @param remove 해제해야할 노드
 * @return t_node* 에러널
 */
static t_node	*cmd_fail(t_node *remove)
{
	t_node	*temp;

	temp = remove;
	while (remove)
	{
		remove = remove->next;
		free_str(temp->arg);
		free(temp);
		temp = remove;
	}
	return (null_err("failed to make next node"));
}

/**
 * 파서
 *
 * @param input 렉서로 입력된 문자열
 * @param env 환경 변수
 * @return t_node* 모든 작업이 포함된 노드
 */
t_node	*parser(char *input, t_env *env)
{
	int		index;
	t_node	*ret;
	t_node	*lst;

	index = 0;
	while (is_space(input[index]) == TRUE_E)
		++index;
	if (input[index] == '\0')
		return (NULL);
	lst = selec_type(input, &index, env);
	if (lst == NULL)
		return (null_err("failed to make first node"));
	ret = lst;
	while (input[index])
	{
		lst->next = selec_type(input, &index, env);
		if (lst->next == NULL)
			return (cmd_fail(ret));
		lst = lst->next;
	}
	lst->next = NULL;
	if (join_cmds(ret) == FALSE_E)
		return (null_err("failed to join split cmd"));
	return (ret);
}
