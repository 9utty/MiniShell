/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:40:23 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:24:52 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 문자를 찾을때까지 문자열을 반복
 *
 * @param str - 반복할 문자열
 * @param index - str의 반복할 위치
 * @param c - 찾을 문자(문자열의 끝)
 */
static void	loop_till_char(char *str, int *index, char c)
{
	while (str[*index] != c && str[*index] != '\0')
		*index += 1;
}

/**
 * @brief - 구분하는 문자열 길이를 구하는 함수
 *
 * @param input - "<<"의 포인터
 * @param ret - 이전함수의 문자열 반복에 필요한
 * @return int
 */
int	get_hdoclen(char *input, int *ret)
{
	int	len;

	len = 0;
	skip_operator_space(input, &len);
	while (input[len] && input[len] != ' ')
	{
		if (input[len] == '"' || input[len] == '\'')
		{
			loop_till_char(input, &len, input[len]);
			len++;
		}
		else
			loop_till_char(input, &len, ' ');
	}
	*ret += len;
	return (len);
}
