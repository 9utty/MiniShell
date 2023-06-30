/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:44:05 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:55:25 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief 두 문자열을 복사하는 함수
 *
 * @param take - 복사할 내용
 * @param place - 복사할 곳
 */
static void	str_copy(char *take, char *place)
{
	int	index;

	index = 0;
	while (take[index])
	{
		place[index] = take[index];
		index++;
	}
	place[index] = '\0';
}

/**
 * @brief - 받은 인덱스 값까지 이중배열을 제거하는 함수
 *
 * @param array - 이중배열의 포인터
 * @param index - 삭제할 최대 인덱스 값 + 1
 * @return NULL
 */
char	**free_array_till_index(char **array, int index)
{
	int	count;

	count = 0;
	while (count < index)
	{
		if (array[count])
			free(array[count]);
		count++;
	}
	if (array)
		free(array);
	return (NULL);
}

/**
 * @brief 환경변수의 갯수를 반환하는 함수
 *
 * @param env_list - 환경변수리스트의 헤드노드
 * @return int - 환경변수의 갯수
 */
int	env_list_size(t_env *env_list)
{
	int	index;

	index = 0;
	while (env_list)
	{
		env_list = env_list->next;
		index++;
	}
	return (index);
}

/**
 * @brief 환경변수 목록을 다시 이중배열로 만드는 함수
 *
 * @param env_list - 환경변수리스트의 헤드
 * @return char** - 성공시
 * @return NULL - 할당 실패
 */
char	**env_list_to_array(t_env *env_list)
{
	t_env	*list;
	char	**env_array;
	int		index;

	index = 0;
	list = env_list;
	env_array = malloc(sizeof(char *) * (env_list_size(env_list) + 1));
	if (!env_array)
		return (NULL);
	while (index < env_list_size(env_list))
	{
		env_array[index] = malloc(sizeof(char) * ft_strlen(list->str) + 1);
		if (!env_array[index])
			return (free_array_till_index(env_array, index));
		str_copy(list->str, env_array[index]);
		index++;
		list = list->next;
	}
	env_array[index] = NULL;
	return (env_array);
}
