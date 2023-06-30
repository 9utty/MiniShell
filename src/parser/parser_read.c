/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:02:17 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 18:23:18 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 종료상태에 문자열 길이 구하는 함수
 *
 * @param strlen - 총 문자열 길이에 대한 포인터
 * @param varlen - 변수의 길이 (이 함수에서는 항상 2)
 * @return int - varlen
 */
int	exit_status_numblen(int *strlen, int varlen)
{
	int	cpy;

	cpy = get_global_data()->exitcode;
	if (cpy == 0)
	{
		*strlen += 1;
		return (varlen);
	}
	while (cpy > 0)
	{
		cpy = cpy / 10;
		*strlen += 1;
	}
	return (varlen);
}

/**
 * @brief - 환경변수의 문자열 길이를 반환하는 함수
 *
 * @param str - '$'를 가진 문자열
 * @param c - 작은 따옴표 또는 큰 따옴표
 * @param strlen - 총 문자열 길이에 대한 포인터
 * @param env - 환경변수
 * @return int - 환경변수의 문자열 길이
 */
int	len_env_str(char *str, char c, int *strlen, t_env *env)
{
	int	varlen;

	varlen = len_env(str, c);
	if (varlen == 2 && str[1] == '?')
		return (exit_status_numblen(strlen, varlen));
	if (varlen == 1)
	{
		if (c == ' ' && (is_space(str[1]) == TRUE_E || str[1] == '\0'))
			*strlen += 1;
		else if (c == '"' || c == '\'')
			*strlen += 1;
		return (varlen);
	}
	while (env)
	{
		if (ft_strncmp(env ->str, str + 1, varlen - 1) == 0
			&& env ->str[varlen - 1] == '=')
		{
			*strlen += ft_strlen(env ->str + varlen);
			break ;
		}
		env = env ->next;
	}
	return (varlen);
}

/**
 * @brief - 공백이 나올때까지의 문자열 길이를 반환하는 함수
 *
 * @param str - 입력된 문자열
 * @param env - 환경변수
 * @param strlen - 문자열 길이에 대한 포인터
 * @return int
 */
static int	len_space(char *str, t_env *env, int *strlen)
{
	int	index;

	index = 0;
	while (is_space(str[index]) == FALSE_E && str[index] != '"'
		&& str[index] != '\'' && str[index] != '\0')
	{
		if (str[index] == '$')
			index += len_env_str(str + index, ' ', strlen, env);
		else
		{
			*strlen += 1;
			++index;
		}
	}
	return (index);
}

/**
 * @brief 문자열에서 따옴표를 확인할때까지의 길이를 계산하는 함수
 *
 * @param str - 입력받은 문자열
 * @param c - 작은따옴표 또는 큰 따옴표
 * @param env - 환경변수
 * @param strlen - 문자열길이에 대한 포인터
 * @return int
 */
static int	len_quote(char *str, char c, t_env *env, int *strlen)
{
	int	index;

	index = 0;
	while (str[index] != c && str[index] != '\0')
	{
		if (c == '"' && str[index] == '$')
			index += len_env_str(str + index, c, strlen, env);
		else
		{
			*strlen += 1;
			++index;
		}
	}
	return (index);
}

/**
 * @brief - 입력한 문자열 길이를 읽는 함수
 *
 * @param str - 입력한 문자열
 * @param strlen - 문자열 길이에 대한 포인터
 * @param env - 환경변수 노드
 */
void	read_input(char *str, int *strlen, t_env *env)
{
	while (*str != '\0' && is_space(*str) == FALSE_E)
	{
		if (*str == '"' || *str == '\'')
		{
			str += len_quote(str + 1, *str, env, strlen);
			if (*(str + 1) == '"' || *(str + 1) == '\'')
				str += 2;
			else
				str += 1;
		}
		else
			str += len_space(str, env, strlen);
	}
}
