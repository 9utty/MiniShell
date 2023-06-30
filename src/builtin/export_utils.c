/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:58:54 by gulee             #+#    #+#             */
/*   Updated: 2022/10/04 12:21:42 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 이중 문자열에서 두 문자열의 포인터 주소를 변경해주는 함수
 *
 * @param string - 이중배열
 * @param str1 - 바꾸어야할 주소
 * @param str2 - 바꾸어야할 주소
 */
static void	swap_strings(char **string, int str1, int str2)
{
	char	*tmp;

	tmp = string[str1];
	string[str1] = string[str2];
	string[str2] = tmp;
}

/**
 * @brief - env를 정렬하는 함수
 *
 * @param env_strings - 정렬해야하는 env들
 * @param lst_size - 문자열 갯수
 */
void	bubble_sort_env(char **env_strings, int lst_size)
{
	int	i;
	int	j;

	while (lst_size-- >= 0)
	{
		i = 0;
		while (env_strings[i] && env_strings[i + 1])
		{
			j = 0;
			while (env_strings[i][j] && env_strings[i + 1][j])
			{
				if ((env_strings[i][j] == '=' || env_strings[i + 1][j] == '=')
					|| (env_strings[i][j] < env_strings[i + 1][j]))
					break ;
				else if (env_strings[i][j] > env_strings[i + 1][j])
				{
					swap_strings(env_strings, i, i + 1);
					break ;
				}
				j++;
			}
			i++;
		}
	}
}

/**
 * @brief - 문자열 앞뒤에 quote넣는 함수 '=' 없다면 없음
 *
 * @param **string - 모든 문자열을 가지고 있는 이중배열
 * @param str - 원래 문자열의 인덱스 번호
 * @param *tmp - quote를 포함해서 들어가야하는 문자열
 * @param *is_equals - 있어?
 *
 */
static void	set_quote_in(char **string, int str, char *tmp, t_bool *is_equals)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (string[str][i])
	{
		tmp[j] = string[str][i];
		if (string[str][i] == '=' && !*is_equals)
		{
			*is_equals = TRUE_E;
			tmp[++j] = '"';
		}
		i++;
		j++;
	}
	if (*is_equals)
		tmp[j] = '"';
	free(string[str]);
	string[str] = tmp;
}

/**
 * @brief - '=' 뒤에 quote 추가하는 함수
 *
 * @param string - 변경해야할 문자열을 포함하는 이중배열
 * @return 0 - 성공
 * @return -1 - 할당실패
 */
int	add_quote_back_equal(char **string)
{
	int		i;
	t_bool	is_equals;
	char	*tmp;

	i = 0;
	while (string[i])
	{
		is_equals = FALSE_E;
		tmp = ft_calloc(ft_strlen(string[i]) + 3, sizeof(char));
		if (!tmp)
			return (-1);
		set_quote_in(string, i, tmp, &is_equals);
		i++;
	}
	return (0);
}

/**
 * @brief - 환경변수리스트에서 문자열을 검색하는 함수
 *
 * @param input - 검색할 문자열
 * @param env - 환경변수리스트
 * @return true - 목록에 있따!
 * @return false - 없어유 ㅠㅠ
 */
t_bool	check_str_in_list(char	*input, t_env *env)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '=' && input[i] != '+')
		i++;
	while (env)
	{
		if (ft_strncmp(input, env->str, i) == 0 && \
		(env->str[i] == '=' || env->str[i] == '\0'))
			return (TRUE_E);
		env = env->next;
	}
	return (FALSE_E);
}
