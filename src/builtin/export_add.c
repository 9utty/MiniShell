/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:56:32 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:51:26 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 추가할지 확인하는 함수
 *
 * @param input - input
 * @return true - 추가혀
 * @return false - 하지마
 */
t_bool	check_append_export(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '+')
			return (TRUE_E);
		else if (input[i] == '=')
			return (FALSE_E);
		i++;
	}
	return (FALSE_E);
}

/**
 * @brief - 환경변수에 문자열을 추가하는 함수
 *
 * @param env - env리스트
 * @param to_add - 넣을 내용
 * @return true - 성공
 * @return false - 할당실패
 */
t_bool	add_env_str(t_env *env, char *to_add)
{
	t_env	*node;
	size_t	size;
	char	*str;
	int		i;

	i = 0;
	node = get_env_node(env, to_add);
	while (to_add[i] && to_add[i] != '=')
		i++;
	if (to_add[i] == '=' && node->is_value)
		i++;
	size = ft_strlen(node->str) + ft_strlen(&to_add[i]) + NULL_E;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (FALSE_E);
	ft_strlcat(str, node->str, size);
	ft_strlcat(str, &to_add[i], size);
	free(node->str);
	node->str = str;
	check_env_is_value(node);
	return (TRUE_E);
}
