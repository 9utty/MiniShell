/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:45:22 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:24:29 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 환경변수에서 찾아야할 문자열이 있는지 체크하는 함수
 *
 * @param str - 환경변수내용
 * @param var - 찾아야할 내용
 * @return int - 0 없네? 1 있네?
 */
static int	cmp_list(char *str, char *var)
{
	int	i;

	i = 0;
	while (str[i] && var[i] && var[i] != '=' && (str[i] == var[i]))
		i++;
	if (var[i] == '+' && var[i + 1] == '=' && \
		(str[i] == '=' || str[i] == '\0'))
		return (0);
	if ((str[i] == '=' && var[i] == '=')
		|| (str[i] == '\0' && var[i] == '\0')
		|| (str[i] == '=' && var[i] == '\0'))
		return (0);
	return (1);
}

/**
 * @brief 해당하는 환경변수를 가져오는 함수
 *
 * @param list - 환경변수리스트의 헤드노드
 * @param variable - 찾아야할 환경변수
 * @return t_env* - 해당하는 노드를 반환
 * @return NULL - 없는경우
 */
t_env	*get_env_node(t_env *list, char *variable)
{
	while (list)
	{
		if (cmp_list(list->str, variable) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
