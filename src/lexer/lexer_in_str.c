/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_in_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:13:56 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:16:48 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief 쌍따옴표 인지 작은따옴표를 다 0으로 초기화 하고 반환
 *
 */
static int	set_and_retrun(int *double_quote, \
					int *single_quote, t_bool return_v)
{
	if (double_quote)
		*double_quote = 0;
	if (single_quote)
		*single_quote = 0;
	return (return_v);
}

/**
 * @brief - 따옴표 안에 있는지 확인하기 위한 함수(반복문에서 사용)
 *
 * @param c - 현재 문자열 내의 문자
 * @param reset - 다음 호출에 방해안되게 내부 데이터 삭제
 * @return true - 따옴표 안에있다면
 * @return false - 없다면
 */
t_bool	in_str(char c, t_bool reset)
{
	static int	double_quote = 0;
	static int	single_quote = 0;

	if (reset)
		return (set_and_retrun(&double_quote, &single_quote, FALSE_E));
	if (c != '\'' && c != '"' && !double_quote && !single_quote)
		return (FALSE_E);
	if (c == '\'' && !double_quote)
	{
		single_quote++;
		if (single_quote == 2)
			return (set_and_retrun(NULL, &single_quote, TRUE_E));
		return (FALSE_E);
	}
	else if (c == '"' && !single_quote)
	{
		double_quote++;
		if (double_quote == 2)
			return (set_and_retrun(&double_quote, NULL, TRUE_E));
		return (FALSE_E);
	}
	return (TRUE_E);
}

/**
 * @brief 문자열 내에서 문자열을 건너뛰기 위한 함수
 *
 * @param str - 문자열
 * @param index - str에 대한 인덱스
 */
void	skip_string(char *str, int *index)
{
	if (str[*index] == '\'')
	{
		*index += 1;
		while (str[*index] != '\'' && str[*index] != '\0')
			*index += 1;
		if (str[*index] == '\'')
			*index += 1;
	}
	else if (str[*index] == '\"')
	{
		*index += 1;
		while (str[*index] != '\"' && str[*index] != '\0')
			*index += 1;
		if (str[*index] == '\"')
			*index += 1;
	}
}
