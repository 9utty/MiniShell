/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:02:12 by gulee             #+#    #+#             */
/*   Updated: 2022/09/12 20:35:32 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - export 출력하면서 ASCII값으로 정렬하는 함수
 *
 * @param env - 환경변수리스트
 * @return 0 - 성공
 * @return -1 - 할당 실패
 */
static int	print_export(t_env *env)
{
	char	**env_strings;
	int		index;

	index = 0;
	env_strings = env_list_to_array(env);
	if (!env_strings)
		return (-1);
	bubble_sort_env(env_strings, env_list_size(env));
	if (add_quote_back_equal(env_strings) == -1)
	{
		free_double_array(env_strings);
		return (-1);
	}
	while (env_strings[index])
	{
		printf("declare -x %s\n", env_strings[index]);
		free(env_strings[index]);
		index++;
	}
	free(env_strings);
	return (0);
}

/**
 * @brief - 입력이 정상인지 체크하는 함수
 *
 * @param inp - 입력값
 * @return 0 - 정상
 * @return -1 - 비정상
 */
static int	check_export_input(char *inp)
{
	int	index;

	index = 0;
	if (inp[0] == '\0' || (inp[0] >= '0' && inp[0] <= '9')
		|| inp[0] == '=' || inp[0] == '+')
	{
		print_error_str(get_err(EXPORT_ERR_E), inp, get_err(IDENT_ERR_E));
		if (get_global_data()->exitcode == 0)
			get_global_data()->exitcode = 1;
		return (-1);
	}
	while (inp[index])
	{
		if (inp[index] == '=' || (inp[index] == '+' && inp[index + 1] == '='))
			break ;
		else if (!(ft_isalnum(inp[index]) || inp[index] == '_'))
		{
			print_error_str(get_err(EXPORT_ERR_E), inp, get_err(IDENT_ERR_E));
			if (get_global_data()->exitcode == 0)
				get_global_data()->exitcode = 1;
			return (-1);
		}
		index++;
	}
	return (0);
}

/**
 * @brief - 새 환경변수노드를 넣는 함수
 *
 * @param input - 넣을 내용을 가지고 있는 문자열
 * @param env - 환경변수 리스트
 * @return 0 - 성공
 * @return -1 - 할당 실패
 */
static int	add_to_list(char *input, t_env **env)
{
	char	*new_str;
	t_bool	past_equals;
	int		index;

	index = 0;
	past_equals = FALSE_E;
	new_str = ft_calloc(ft_strlen(input) + NULL_E, sizeof(char));
	if (!new_str)
		return (-1);
	while (*input)
	{
		if (*input == '+' && past_equals == FALSE_E)
			input++;
		if (*input == '=')
			past_equals = TRUE_E;
		new_str[index] = *input;
		input++;
		index++;
	}
	if (add_env_node(env, new_str) == -1)
	{
		free(new_str);
		return (-1);
	}
	return (0);
}

/**
 * @brief - 입력과 동일한 변수 이름을 포함하는 노드 내부의 현재 값을
 * 			대체하는 함수
 *
 * @param input - 설정해야하는 새로운 값을 가진 문자열
 * @param env - 환경변수리스트
 * @return true - 성공
 * @return false - 할당 실패
 */
static int	relpace_in_list(char *input, t_env *env)
{
	t_env	*to_replace;
	char	*variable;
	int		index;

	index = 0;
	if (check_append_export(input))
		return (add_env_str(env, input));
	variable = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!variable)
		return (FALSE_E);
	while (input[index] && input[index] != '=')
	{
		variable[index] = input[index];
		index++;
	}
	to_replace = get_env_node(env, variable);
	while (input[index])
	{
		variable[index] = input[index];
		index++;
	}
	free(to_replace->str);
	to_replace->str = variable;
	check_env_is_value(to_replace);
	return (TRUE_E);
}

/**
 * @brief - export를 실행하는 함수
 *
 * @param args - 실행할때 사용할 인자를 가지고 있는 이중배열
 * @param env - 환경변수리스트
 * @return 0 - 성공
 * @return -1 - 할당 실패
 */
int	export(char **args, t_env **env)
{
	int	i;

	i = 0;
	get_global_data()->exitcode = 0;
	if (!*args)
		return (print_export(*env));
	while (args[i])
	{
		if (check_export_input(args[i]) == -1 || (args[i][0] && \
			args[i][0] == '_' && (args[i][1] == '=' || args[i][1] == '\0')))
		{
			i++;
			continue ;
		}
		else if (check_str_in_list(args[i], *env))
		{
			if (relpace_in_list(args[i], *env) == -1)
				return (-1);
		}
		else if (add_to_list(args[i], env) == -1)
			return (-1);
		i++;
	}
	return (0);
}
