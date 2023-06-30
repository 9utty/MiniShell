/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:45:50 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 18:52:08 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 하나의 큰 따옴표가 나올때까지 복사
 *
 * @param dst - 복사할 위치
 * @param src - 복사할 문자열
 * @param index - 소스의 반복할 위치
 * @param env - 환경변수
 * @return int - 복사한 문자열 길이
 */
static int	cpy_till_quote(char *dst, char *src, int *index, t_env *env)
{
	char	c;
	int		count;

	c = src[*index];
	*index += 1;
	count = 0;
	while (src[*index] != '\0' && src[*index] != c)
	{
		if (src[*index] == '$' && c == '"')
			*index += in_env_till_quote(dst + count, src + *index, env, &count);
		else
		{
			dst[count] = src[*index];
			*index += 1;
			++count;
		}
	}
	if (src[*index] == c)
		*index += 1;
	return (count);
}

/**
 * @brief - 공백을 볼때까지 복사
 *
 * @param dst - 복사할 위치
 * @param src - 복사할 소스
 * @param index - 소스의 반복할 위치 포인터
 * @param env - 환경변수
 * @return int - 복사된 문자열 길이 반환
 */
static int	cpy_till_space(char *dst, char *src, int *index, t_env *env)
{
	int	count;

	count = 0;
	while (src[*index] != '\0' && is_space(src[*index]) == FALSE_E
		&& src[*index] != '"' && src[*index] != '\'')
	{
		if (src[*index] == '$')
			*index += in_env_till_sapce(dst + count, src + *index, env, &count);
		else
		{
			dst[count] = src[*index];
			*index += 1;
			++count;
		}
	}
	return (count);
}

/**
 * @brief - node에 문자열을 넣기
 *
 * @param dst - 넣어야할 위치
 * @param src - 소스 문자열
 * @param index - 소스의 반복할 위치의 포인터
 * @param env 환경 변수
 */
void	in_str_out_node(char *dst, char *src, int *index, t_env *env)
{
	int	count;

	count = 0;
	while (src[*index] != '\0' && is_space(src[*index]) == FALSE_E)
	{
		if (src[*index] == '"' || src[*index] == '\'')
			count += cpy_till_quote(dst + count, src, index, env);
		else
			count += cpy_till_space(dst + count, src, index, env);
	}
	dst[count] = '\0';
	while (is_space(src[*index]) == TRUE_E)
		*index += 1;
}
