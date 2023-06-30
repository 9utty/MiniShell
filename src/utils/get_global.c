/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_global.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:17:23 by gulee             #+#    #+#             */
/*   Updated: 2022/09/12 20:42:11 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 어디서든 불러올 수 있는 global data
 *
 * @return t_global_data*
 */
t_global_data	*get_global_data(void)
{
	static t_global_data	global_data;

	return (&global_data);
}

/**
 * @brief - 출력할 에러메시지를 반환하는 함수
 *
 * @param code - 반환할 index
 * @return char*
 */
char	*get_err(t_err_code code)
{
	static char	*error[] = {
		"\033[1;31mminishell: .: filename argument required\n .: usage: . filename \
		[arguments]\033[0m\n", \
		"\033[1;31mminishell: you've comitted a sintax near unexpected \
		 token \033[0m", \
		"\033[1;31mminishell: you've comitted a sintax error near \
		unexpected token `newline'\033[0m\n", \
		"\033[1;31mminishell: pipe: Resource temporarily unavailable\033[0m\n", \
		"\033[1;31mminishell: fork: Resource temporarily unavailable\n", \
		"\033[1;31mminishell: unset: \033[0m\n", \
		"\033[1;31mminishell: export: \033[0m\n", \
		"\033[1;31m': not a valid identifier\033[0m\n\n", \
		"\033[1;31m: ambiguous redirect\033[0m\n\n"
	};

	return (error[code]);
}
