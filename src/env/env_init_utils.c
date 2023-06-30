/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:35:29 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:09:17 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 문자열에서 다른 문자열로 복사하는 함수
 *
 * @param take - 복사할 내용을 가지고 있는 문자열
 * @param place - 복사할 위치
 */
static void	str_copy(char *take, char *place)
{
	int	i;

	i = 0;
	while (take[i])
	{
		place[i] = take[i];
		i++;
	}
	place[i] = '\0';
}

/**
 * @brief OLDPWD의 값을 제거하는 함수
 *
 * @param list - 환경변수리스트의 헤드
 */
static void	del_old_pwd(t_env **list)
{
	t_env	*tmp;

	tmp = get_env_node(*list, "OLDPWD=");
	if (tmp)
	{
		tmp->str[6] = '\0';
		tmp->is_value = FALSE_E;
	}
}

/**
 * @brief - 쉘레벨을 1씩 증가시키는 함수
 *
 * @param list - 환경변수의 목록
 * @return - 0 성공시 -1 할당실패
 */
static int	update_shell_level(t_env *list)
{
	int		level;
	char	*new_str;
	char	*new_num;

	list = get_env_node(list, "SHLVL");
	if (!list)
		return (0);
	level = ft_atoi(&list->str[6]);
	level++;
	new_num = ft_itoa(level);
	if (!new_num)
		return (-1);
	new_str = malloc(sizeof(char) * (ft_strlen(new_num) + 7));
	if (!new_str)
	{
		free(new_num);
		return (-1);
	}
	str_copy("SHLVL=", new_str);
	ft_strlcat(new_str, new_num, ft_strlen(new_num) + 7);
	free(new_num);
	free(list->str);
	list->str = new_str;
	return (0);
}

/**
 * @brief - 환경변수 리스트에서 삭제하는 함수
 *
 * @param list - 환경변수리스트의 헤드노드
 */
static void	remove_env_list(t_env **list)
{
	t_env	*pre;
	t_env	*tmp;
	t_env	*next;
	int		i;

	i = 0;
	del_old_pwd(list);
	tmp = *list;
	while (tmp)
	{
		if (ft_strncmp("_=", tmp->str, 2) == 0)
		{
			next = tmp->next;
			free(tmp->str);
			free(tmp);
			if (i == 0)
				*list = next;
			else
				pre->next = next;
			tmp = pre;
		}
		i++;
		pre = tmp;
		tmp = tmp->next;
	}
}

/**
 * @brief - 환경변수 목록을 정리하고 쉘레벨을 1증가시키는 함수
 *
 * @param env_head - 환경변수 리스트의 헤드노드
 * @return true - 성공
 * @return false - 실패(할당실패)
 */
t_bool	sort_env_list(t_env **env_head)
{
	check_env_value(*env_head);
	remove_env_list(env_head);
	if (update_shell_level(*env_head) == -1)
		return (del_env_false(env_head));
	return (TRUE_E);
}
