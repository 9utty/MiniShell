/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:30:37 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 18:36:52 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 따옴표가 있을때까지 문자열을 복사
 *
 * @param dst - 복사할 위치
 * @param src - 복사할 문자열
 * @param index - 소스의 반복위치
 * @return int - 복사한 길이
 */
int	cpy_hdoc_till_quote(char *dst, char *src, int *index)
{
	char	c;
	int		count;

	c = src[*index];
	*index += 1;
	count = 0;
	while (src[*index] != '\0' && src[*index] != c)
	{
		dst[count] = src[*index];
		*index += 1;
		++count;
	}
	if (src[*index] == c)
		*index += 1;
	return (count);
}

/**
 * @brief - heredoc 문자열을 문자열에 넣기
 *
 * @param dst - 넣을 위치
 * @param src - 원본 문자열
 * @param index - 소스 문자열 반복위치
 */
void	in_hdoc_out_str(char *dst, char *src, int *index)
{
	int	count;

	count = 0;
	while (src[*index] != '\0' && is_space(src[*index]) == FALSE_E)
	{
		if (src[*index] == '"' || src[*index] == '\'')
			count += cpy_hdoc_till_quote(dst + count, src, index);
		else
		{
			while (src[*index] != '\0' && is_space(src[*index]) == FALSE_E
				&& src[*index] != '"' && src[*index] != '\'')
			{
				dst[count] = src[*index];
				*index += 1;
				++count;
			}
		}
	}
	dst[count] = '\0';
	while (is_space(src[*index]) == TRUE_E)
		*index += 1;
}

/**
 * @brief - 공백이 나올때까지 문자를 읽는 함수
 *
 * @param str - 읽을 문자열
 * @param len - 총 문자열 길이에 대한 포인터
 * @return int - 읽은 길이 반환
 */
static int	len_space(char *str, int *len)
{
	int	index;

	index = 0;
	while (is_space(str[index]) == FALSE_E && str[index] != '"'
		&& str[index] != '\'' && str[index] != '\0')
	{
		*len += 1;
		++index;
	}
	return (index);
}

/**
 * @brief - 따옴표가 나올때까지 문자열을 읽는 함수
 *
 * @param str - 읽을 문자열
 * @param c - 작은따옴표 또는 큰 따옴표
 * @param len - 총 문자열의 길이에 대한 포인터
 * @return int - 따옴표가 나올때까지의 문자열 길이
 */
static int	len_quote(char *str, char c, int *len)
{
	int	index;

	index = 0;
	while (str[index] != c && str[index] != '\0')
	{
		*len += 1;
		++index;
	}
	return (index);
}

/**
 * @brief - heredoc의 구분 문자의 문자열길이를 구하는 함수
 *
 * @param str - 탐색핢 문자열
 * @param len - 총 문자열 길이에 대한 포인터
 */
void	read_hdoc(char *str, int *len)
{
	while (*str != '\0' && is_space(*str) == FALSE_E)
	{
		if (*str == '"' || *str == '\'')
		{
			str += len_quote(str + 1, *str, len);
			if (*(str + 1) == '"' || *(str + 1) == '\'')
				str += 2;
			else
				str += 1;
		}
		else
			str += len_space(str, len);
	}
}
