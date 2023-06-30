/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:47:00 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 18:55:09 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 종료상태 복사
 *
 * @param dst - 복사할 위치
 * @param index - dst의 총 문자열 길이
 */
void	interp_exit_status(char *dst, int *index)
{
	int	count;
	int	cpy;

	count = 0;
	cpy = get_global_data()->exitcode;
	if (cpy == 0)
	{
		dst[count] = '0';
		*index += 1;
		return ;
	}
	while (cpy > 0)
	{
		cpy = cpy / 10;
		++count;
	}
	cpy = get_global_data()->exitcode;
	--count;
	while (cpy > 0)
	{
		dst[count] = cpy % 10 + '0';
		cpy = cpy / 10;
		--count;
		*index += 1;
	}
}

/**
 * @brief - 걸러진 환경변수를 복사
 *
 * @param dst - 복사할 위치
 * @param src - 복사할 내용
 * @param env - 환경변수
 * @param varlen - 걸러지지 않은 변수의 길이
 * @return int 함수로 적용된 길이 반환
 */
int	cpy_env_to_str(char *dst, char *src, t_env *env, int varlen)
{
	int	ret;

	ret = 0;
	while (env)
	{
		if (ft_strncmp(env ->str, src + 1, varlen - 1) == 0
			&& env ->str[varlen - 1] == '=')
		{
			ft_strlcpy(dst, env ->str + varlen,
				ft_strlen(env ->str + varlen) + 1);
			ret += ft_strlen(env ->str + varlen);
		}
		env = env->next;
	}
	return (ret);
}

/**
 * @brief 따옴표가 나올때까지 환경변수를 넣는다
 *
 * @param dst - 넣을 위치
 * @param src - 넣을 소스
 * @param env - 환경변수
 * @param count - 처리가 안된 변수의 길이
 * @return int 처리가 안된 변수의 길이 반환
 */
int	in_env_till_quote(char *dst, char *src, t_env *env, int *count)
{
	int	varlen;

	varlen = len_env(src, '"');
	if (varlen == 2 && src[1] == '?')
	{
		interp_exit_status(dst, count);
		return (varlen);
	}
	if (varlen == 1)
	{
		*dst = '$';
		*count += 1;
		return (varlen);
	}
	*count += cpy_env_to_str(dst, src, env, varlen);
	return (varlen);
}

/**
 * @brief - 공백이 나올때까지 환경변수를 넣는 함수
 *
 * @param dst - 넣을 위치
 * @param src - 넣을 소스
 * @param env - 환경변수
 * @param count - dst의 위치
 * @return int
 */
int	in_env_till_sapce(char *dst, char *src, t_env *env, int *count)
{
	int	varlen;

	varlen = len_env(src, '"');
	if (varlen == 2 && src[1] == '?')
	{
		interp_exit_status(dst, count);
		return (varlen);
	}
	if (varlen == 1)
	{
		if (is_space(src[1]) == TRUE_E || src[1] == '\0')
		{
			*dst = '$';
			*count += 1;
		}
		return (varlen);
	}
	*count += cpy_env_to_str(dst, src, env, varlen);
	return (varlen);
}
