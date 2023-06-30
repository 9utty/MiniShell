/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:41:10 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:26:04 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 환경변수리스트의 첫번째를 생성하고 초기화 하는 함수
 *
 * @param head - 환경변수리스트의 헤드주소
 * @param str - 첫번째 노드의 내용
 * @return 0 - 성공
 * @return -1 - 할당 실패
 */
int	set_first_node(t_env **head, char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env) * 1);
	if (!new)
		return (-1);
	new->next = NULL;
	new->str = str;
	check_env_is_value(new);
	*head = new;
	return (0);
}

/**
 * @brief - 새로운 내용을 가지고 있는 env노드를 추가하는 함수
 *
 * @param env - 환경변수리스트
 * @param str - 새로 추가할 내용
 * @return 0 - 성공
 * @return -1 - 할당 실패
 */
int	add_env_node(t_env **env, char *str)
{
	t_env	*new;

	if (!*env)
	{
		if (set_first_node(env, str) == -1)
			return (-1);
		return (0);
	}
	new = *env;
	while (new->next)
		new = new->next;
	new->next = malloc(sizeof(t_env) * 1);
	if (!new->next)
		return (-1);
	new = new->next;
	new->next = NULL;
	new->str = str;
	check_env_is_value(new);
	return (0);
}
