/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:46:52 by gulee             #+#    #+#             */
/*   Updated: 2022/09/09 21:25:20 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 전체 env를 출력하는 함수
 *
 * @param list - 환경변수리스트
 */
void	env(t_env *list)
{
	while (list)
	{
		if (list->is_value)
			printf("%s\n", list->str);
		list = list->next;
	}
	get_global_data()->exitcode = 0;
}
