/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:34:09 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:28:45 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief 명령어 개수 가져오는 함수
 *
 * @param str - 탐색할 문자열
 * @return int - 개수
 */
int	get_cmd_count(char *str)
{
	int	index;
	int	ret;

	index = 0;
	ret = 0;
	while (str[index] != '\0' && is_operator(str[index]) == FALSE_E)
	{
		while (str[index] != '\0')
		{
			if (is_space(str[index]) == TRUE_E)
			{
				while (is_space(str[index]) == TRUE_E)
					++index;
				break ;
			}
			else if (str[index] == '"' || str[index] == '\'')
				index += skip_str(str + index, str[index]);
			else
				++index;
		}
		++ret;
	}
	return (ret);
}

/**
 * @brief cmdnode 생성 및 초기화
 *
 * @param arrlen data의 배열 길이
 * @return t_node*
 */
t_node	*init_cmd(int arrlen)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (null_err("Allocation failure error in init cmd"));
	node ->arg = malloc(sizeof(char *) * (arrlen + 1));
	if (node ->arg == NULL)
	{
		free(node);
		return (null_err("Allocation failure error in init cmd"));
	}
	node->next = NULL;
	return (node);
}

/**
 * @brief - 문제가 생겼을때 노드를 삭제하는 함수
 *
 * @param node - 삭제할 노드
 * @param count - data의 길이
 * @return t_node*
 */
t_node	*arg_malloc_fail(t_node *node, int count)
{
	--count;
	while (count >= 0)
	{
		printf("freeing %s\n", node ->arg[count]);
		free(node->arg[count]);
		--count;
	}
	free(node->arg);
	free(node);
	return (null_err("Allocation failure error in arg malloc fail"));
}

t_node	*space_edge_case(void)
{
	t_node	*ret;

	ret = malloc(sizeof(t_node));
	if (ret == NULL)
		return (NULL);
	ret->arg = malloc(sizeof(char *) * 2);
	if (ret->arg == NULL)
	{
		free(ret);
		return (NULL);
	}
	ret->arg[0] = ft_strdup("");
	if (ret ->arg[0] == NULL)
	{
		free(ret->arg);
		free(ret->arg[0]);
		return (NULL);
	}
	ret->type = TOSTDOUT_E;
	ret->arg[1] = NULL;
	return (ret);
}

/**
 * @brief - 각 명령어 타입으로 노드를 만드는 함수
 *
 * @param input - lexer로 처리한 문자열
 * @param index - input 문자열을 탐색하기 위한 위치
 * @param envp - 환경변수
 * @return t_node*
 */
t_node	*parser_cmd(char *input, int *index, t_env *envp)
{
	t_node	*node;
	int		strlen;
	int		cmdarrlen;
	int		count;

	count = 0;
	if (input[*index] == '\0')
		return (space_edge_case());
	cmdarrlen = get_cmd_count(input + *index);
	node = init_cmd(cmdarrlen);
	if (node == NULL)
		return (null_err("failed to create cmd node"));
	while (cmdarrlen > count)
	{
		strlen = 0;
		read_input(input + *index, &strlen, envp);
		node ->arg[count] = malloc(sizeof(char) * strlen + 1);
		if (node ->arg[count] == NULL)
			return (arg_malloc_fail(node, count));
		in_str_out_node(node ->arg[count], input, index, envp);
		count++;
	}
	node ->type = TOSTDOUT_E;
	node ->arg[count] = NULL;
	return (node);
}
