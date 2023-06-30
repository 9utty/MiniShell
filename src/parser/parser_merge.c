/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:42:30 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:10:40 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 문자열의 개수를 확인하는 함수
 *
 * @param arr - 확인할 문자열들
 * @return int - 문자열 개수
 */
static int	count_str(char **arr)
{
	int	count;

	count = 0;
	while (*arr != NULL)
	{
		count++;
		arr++;
	}
	return (count);
}

/**
 * @brief - 배열을 복사하는 함수
 *
 * @param ret - 최종 반환 배열
 * @param str1 - 복사할 문자열
 * @param str2 - 복사할 문자열
 * @return true - 성공시
 * @return false - 실패시
 */
static t_bool	dup_str(char **ret, char **str1, char **str2)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str1[index] != NULL)
	{
		ret[index] = ft_strdup(str1[index]);
		if (ret[index] == NULL)
			return (bool_err("Allocation failure error in dup_str"));
		++index;
	}
	while (str2[count] != NULL)
	{
		ret[index] = ft_strdup(str2[count]);
		if (ret[index] == NULL)
			return (bool_err("Allocation failure error in dup_str"));
		++index;
		++count;
	}
	ret[index] = NULL;
	return (TRUE_E);
}

/**
 * @brief - 두개의 문자열을 합치는 함수
 *
 * @param str1 - 합칠 문자열
 * @param str2 - 합칠 문자열
 * @return char** - 합쳐진 문자열
 */
static char	**join_str(char **str1, char **str2)
{
	int		len;
	char	**ret;

	len = count_str(str1) + count_str(str2);
	ret = malloc(sizeof(char *) * (len + 1));
	if (ret == NULL)
		return (null_err("Allocation failure error in join_str"));
	if (dup_str(ret, str1, str2) == FALSE_E)
	{
		free_double_array(ret);
		return (NULL);
	}
	return (ret);
}

/**
 * @brief - dst와 src를 합치는 함수
 *
 * @param dst - 대상노드
 * @param src - 내용을 dst에 넣고 지울 노드
 * @param next - 이전노드의 다음 포인터
 * @return t_bool - 성공시 TRUE
 */
t_bool	merge_cmd(t_node *dst, t_node **src, t_node **next)
{
	char	**curr_dst;
	char	**curr_src;
	t_node	*remove;

	curr_dst = dst->arg;
	curr_src = (*src)->arg;
	remove = *src;
	dst->arg = join_str(curr_dst, curr_src);
	if (dst->arg == NULL)
		return (FALSE_E);
	*next = (*src)->next;
	*src = (*src)->next;
	free_double_array(curr_dst);
	free_double_array(curr_src);
	free(remove);
	return (TRUE_E);
}
