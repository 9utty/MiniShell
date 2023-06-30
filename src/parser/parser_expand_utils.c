/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:28:58 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 18:49:40 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 연산자들 뒤에 오는 공백 복사
 *
 * @param dst - 복사할 위치
 * @param src - 복사할 내용
 * @param index - 반복할 위치
 */
static void	cpy_operator_space(char *dst, char *src, int *index)
{
	while (is_space(src[*index]) == FALSE_E)
	{
		dst[*index] = src[*index];
		*index += 1;
	}
	while (is_space(src[*index]) == TRUE_E)
	{
		dst[*index] = src[*index];
		*index += 1;
	}
}

/**
 * @brief - 따옴표로 된 문자열을 복사
 *
 * @param dst - 복사할 위치
 * @param src - 복사할 소스
 * @param index - 반복할 위치
 */
static void	cpy_delimit(char *dst, char *src, int *index)
{
	char	c;

	c = src[*index];
	dst[*index] = src[*index];
	*index += 1;
	while (src[*index] != '\0' && src[*index] != c)
	{
		dst[*index] = src[*index];
		*index += 1;
	}
	if (src[*index] == c)
	{
		dst[*index] = src[*index];
		*index += 1;
	}
}

/**
 * @brief - 공백공간 복사
 *
 * @param dst - 복사할 위치
 * @param src - 복사할 소스
 * @param index - dst, src의 위치에 대한 포인터
 */
void	cpy_space(char *dst, char *src, int *index)
{
	while (is_space(src[*index]) == TRUE_E)
	{
		dst[*index] = src[*index];
		*index += 1;
	}
}

/**
 * @brief - 일단 복사하는 함수
 *
 * @param dst - 복사할 위치
 * @param src - 복사할 내용
 * @param index - 함수콜에서의 반복하는 위치
 * @return int - 문자열 길이
 */
int	cpy_once(char *dst, char *src, int *index)
{
	int	count;

	count = 0;
	cpy_operator_space(dst, src, &count);
	while (src[count] != '\0' && is_space(src[count]) == FALSE_E)
	{
		if (src[count] == '"' || src[count] == '\'')
			cpy_delimit(dst, src, &count);
		else
		{
			while (src[count] != '\0' && is_space(src[count]) == FALSE_E \
				&& src[count] != '"' && src[count] != '\'')
			{
				dst[count] = src[count];
				++count;
			}
		}
	}
	*index += count;
	return (count);
}

/**
 * @brief - 문자 하나를 dst에 복사하는 함수
 *
 * @param dst - 복사할 장소
 * @param src - 복사할 내용
 * @param i - 작업을 위한 인덱스
 * @param count - 작업을 위한 인덱스
 */
void	cpy_char(char *dst, char *src, int *index, int *count)
{
	dst[*count] = src[*index];
	*index += 1;
	*count += 1;
}
