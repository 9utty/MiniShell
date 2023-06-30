/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:31:36 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:09:20 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - env로 새로운 env노드를 만드는 함수
 *
 * @param env - env의 내용을 담고 있는 문자열
 * @return t_env* - envp의 내용을 담고 있는 env list를 반환
 */
static t_env	*new_env_node(char *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->str = ft_strdup(env);
	if (!new->str)
	{
		free (new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

/**
 * @brief 환경변수 리스트를 만드는 함수
 *
 * @param env - 환경변수 리스트로 만들어야 하는 정보를 닮고 있는 이중배열
 * @param env_head - 변환한 환경변수를 저장할 env 리스트
 * @return true - 성공시
 * @return false - 실패시
 */
t_bool	init_env_list(char **env, t_env **env_head)
{
	t_env	*tmp;
	t_env	*new;
	int		index;

	index = 0;
	while (env[index])
	{
		new = new_env_node(env[index]);
		if (!new)
			return (del_env_false(env_head));
		if (index == 0)
		{
			tmp = new;
			*env_head = tmp;
			++index;
			continue ;
		}
		else
			tmp->next = new;
		tmp = tmp->next;
		++index;
	}
	return (sort_env_list(env_head));
}
