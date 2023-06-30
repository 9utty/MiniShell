/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:02:32 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:22:09 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 환경변수리스트를 삭제하고 false를 반환하는 함수
 *
 * @param env - 환경변수리스트의 헤드
 * @return t_bool
 */
t_bool	del_env_false(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	while (tmp)
	{
		if (tmp->str)
			free(tmp->str);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*env = NULL;
	return (FALSE_E);
}

/**
 * @brief - 이중배열을 삭제하는 함수
 *
 * @param array - 삭제할 이중배열
 */
void	free_double_array(char **array)
{
	int	index;

	index = 0;
	if (array)
	{
		while (array[index])
		{
			free(array[index]);
			index++;
		}
		free(array);
	}
}

/**
 * @brief - node의 첫번째를 지우는 함수
 *
 * @param node - 노드의 헤드주소
 */
void	del_cmd_node(t_node **node)
{
	t_node	*next;

	if (!node || !*node)
		return ;
	free_double_array((*node)->arg);
	next = (*node)->next;
	free((*node));
	*node = next;
}

/**
 * @brief 전체 노드를 삭제하는 함수
 *
 * @param node - 노드의 헤드주소
 */
void	del_cmd_list(t_node **node)
{
	while (node && *node)
		del_cmd_node(node);
}
