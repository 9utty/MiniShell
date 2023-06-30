/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:31:00 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 18:18:46 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 문자열에서 '\0'문자가 있는 위치를 확인하는 함수
 *
 * @param str - 확인할 문자열
 * @param index - 현재 문자열의 위치
 * @param n - 확인해야할 카운트
 * @return int - '\0'의 위치가 있는 인덱스
 */
int	str_end(char *str, int index, int n)
{
	int	count;

	count = 0;
	while (count <= n && str[index + count] != '\0')
		++count;
	return (count - 1);
}

/**
 * @brief - 연산자인지 확인하는 함수
 *
 * @param c - 확인할 문자
 * @return t_bool - 맞다면 TRUE 아니면 FALSE
 */
t_bool	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (TRUE_E);
	return (FALSE_E);
}

/**
 * @brief 변수의 길이를 확인하는 함수
 *
 * @param str - str[0] == '$'를 포함하는 문자열
 * @param end - 필요없음
 * @return int 변수의 길이 반환
 */
int	len_env(char *str, char end)
{
	int	ret;

	ret = 1;
	if (str[ret] == '?')
		return (2);
	while (ft_isalnum(str[ret]) == TRUE_E)
		++ret;
	(void) end;
	return (ret);
}

/**
 * @brief - 문자가 공백인지 검사하는 함수
 *
 * @param c - 확인할 캐릭터
 * @return t_bool - 맞다면 TRUE_E, 틀리다면 FALSE_E
 */
t_bool	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (TRUE_E);
	return (FALSE_E);
}

/**
 * @brief - 쿼트로 묶인 문자열 스킵을 위한 함수
 *
 * @param str - 확인할 문자열
 * @param quote - s or d 쿼트
 * @return int - 건너 뛸 인덱스
 */
int	skip_str(char *str, char quote)
{
	int	index;

	index = 1;
	while (str[index] != quote && str[index] != '\0')
		++index;
	if (str[index] == quote)
		return (index + 1);
	return (index);
}
