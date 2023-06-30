/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:31:58 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:02:58 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 리스트에서 환경변수를 지우는 함수
 *
 * @param arg - 모든 것을 담고 있는 이중배열
 * @param list - 환경변수리스트
 */
static void	del_form_env(char *arg, t_env **list)
{
	t_env	*pre;
	t_env	*tmp;
	t_env	*next;
	int		index;

	index = 0;
	tmp = *list;
	while (tmp)
	{
		if (ft_strncmp(arg, tmp->str, ft_strlen(arg)) == 0)
		{
			next = tmp->next;
			free(tmp->str);
			free(tmp);
			if (index == 0)
				*list = next;
			else
				pre->next = next;
			break ;
		}
		++index;
		pre = tmp;
		tmp = tmp->next;
	}
}

/**
 * @brief - 입력이 맞는지 체크하는 함수
 *
 * @param str - 체크해야하는 문자열
 * @return true - 잘못된 입력
 * @return false - 정상적인 입력
 */
static t_bool	check_unset(char *str)
{
	int	index;

	index = 0;
	if (str[0] == '\0' || ft_isdigit(str[0]))
		return (return_erremsg(get_err(UNSET_ERR_E), \
			str, get_err(IDENT_ERR_E), 1));
	while (str[index])
	{
		if (!ft_isalnum(str[index]) && str[index] != '_')
		{
			get_global_data()->exitcode = 1;
			return (return_erremsg(get_err(UNSET_ERR_E), \
					str, get_err(IDENT_ERR_E), TRUE_E));
		}
		++index;
	}
	return (FALSE_E);
}

/**
 * @brief - 환경변수에서 해당하는 노드를 지우는 함수
 *
 * @param arg - 모든 인자를 가지고 있는 이중배열
 * @param list - 환경변수리스트
 *
*/
void	unset(char **arg, t_env **list)
{
	int	index;

	index = 0;
	get_global_data()->exitcode = 0;
	while (arg[index])
	{
		if (!check_unset(arg[index]))
			del_form_env(arg[index], list);
		index++;
	}
}
