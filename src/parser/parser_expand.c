/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:17:09 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 18:52:04 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 문자열에 작은따옴표나 큰따옴표가 없는지 확인하는함수
 *
 * @param type - 현재 상태
 * @param c - 검사할 문자열
 * @return int - 상태 업데이트
 */
static int	check_type(int type, char c)
{
	if (c == '"' && type == SPACE_E)
		type = DOUBLE_E;
	else if (c == '"' && type == DOUBLE_E)
		type = SPACE_E;
	if (c == '\'' && type == SPACE_E)
		type = SINGLE_E;
	else if (c == '\'' && type == SINGLE_E)
		type = SPACE_E;
	return (type);
}

/**
 * @brief - 애매한 redir확인하는 함수
 *
 * @param str - 체크할 문자열
 * @param index - str의 반복
 * @param type - "" / '' / ' '
 * @param env - 환경변수 목록
 * @return true - 있다면
 * @return false - 없다면
 */
static t_bool	check_if_ambigu(char *str, int index, int type, t_env *env)
{
	if (!(str[index] == '<' && str[index + 1] == '<')
		&& (str[index] == '<' || str[index] == '>')
		&& ambigu_redirect(str, index, env) == TRUE_E
		&& type != SINGLE_E)
		return (TRUE_E);
	return (FALSE_E);
}

/**
 * @brief - 입력된 문자열을 새로운 문자열에 넣는 함수
 *
 * @param dst - 넣을 위치
 * @param src - 복사할 문자열
 * @param env - 환경변수 목록
 */
static void	expand_stcpy(char *dst, char *src, t_env *env)
{
	int	index;
	int	j;
	int	type;

	index = 0;
	j = 0;
	type = SPACE_E;
	while (src[index])
	{
		type = check_type(type, src[index]);
		if (src[index] == '<' && src[index + 1] == '<' && type == SPACE_E)
			j += cpy_once(dst + j, src + index, &index);
		else if (check_if_ambigu(src, index, type, env) == TRUE_E)
			j += cpy_once(dst + j, src + index, &index);
		else if (src[index] == '$' && type == SPACE_E)
			index += in_env_till_sapce(dst + j, src + index, env, &j);
		else if (src[index] == '$' && type == DOUBLE_E)
			index += in_env_till_quote(dst + j, src + index, env, &j);
		else
			cpy_char(dst, src, &index, &j);
	}
	dst[j] = '\0';
}

/**
 * @brief - 입력된 문자열의 길이를 반환하는 함수
 *
 * @param input - lexer에서 보낸 문자열
 * @param env - 환경변수 목록
 * @return int - 구문분석이 된 문자열의 길이
 */
static int	len_input(char *input, t_env *env)
{
	int	index;
	int	ret;
	int	type;

	index = 0;
	ret = 0;
	type = SPACE_E;
	while (input[index])
	{
		type = check_type(type, input[index]);
		if (input[index] == '<' && input[index + 1] == '<' && type == SPACE_E)
			index += get_hdoclen(input + index, &ret);
		else if (check_if_ambigu(input, index, type, env) == TRUE_E)
			index += get_hdoclen(input + index, &ret);
		else if (input[index] == '$' && type == SPACE_E)
			index += len_env_str(input + index, ' ', &ret, env);
		else if (input[index] == '$' && type == DOUBLE_E)
			index += len_env_str(input + index, '"', &ret, env);
		else
		{
			ret++;
			index++;
		}
	}
	return (ret);
}

/**
 * @brief - 환경변수를 확장하는 함수
 *
 * @param input - lexer로 입력된 문자열
 * @param env - 환경변수 목록
 * @return char* - 확장된 환경변수
 */
char	*expander(char *input, t_env *env)
{
	char	*ret;
	int		size;

	if (!input)
		return (NULL);
	size = len_input(input, env);
	ret = malloc(size + 1);
	if (ret == NULL)
	{
		free(input);
		return (NULL);
	}
	expand_stcpy(ret, input, env);
	free(input);
	return (ret);
}
