/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:27:44 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:26:53 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 파이프 노드 생성
 *
 * @param input - 파이프인 문자열
 * @param index - 문자열의 인덱스
 * @return t_node* - 파이프 노드 반환
 */
t_node	*parser_pipe(char *input, int *index)
{
	t_node	*ret;

	ret = malloc(sizeof(t_node));
	if (ret == NULL)
		return (null_err("Allocation failure error in parser pipe"));
	ret->type = PIPE_E;
	ret->arg = NULL;
	*index += 1;
	while (input[*index] != '\0' && is_space(input[*index]))
		*index += 1;
	return (ret);
}
