/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:39:35 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:25:44 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 환경변수에 value가 있는지 체크
 *
 * @param env - 환경변수리스트
 */
void	check_env_is_value(t_env *env)
{
	int	i;

	i = 0;
	if (env)
	{
		env->is_value = FALSE_E;
		while (env->str[i])
		{
			if (env->str[i] == '=')
				env->is_value = TRUE_E;
			i++;
		}
	}
}

/**
 * @brief 환경변수리스트에서 모든 변수의 값이 있는지 체크하는 함수
 *
 * @param env - 환경변수리스트의 헤드
 */
void	check_env_value(t_env *env)
{
	while (env)
	{
		check_env_is_value(env);
		env = env->next;
	}
}
