/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambigu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:35:33 by gulee             #+#    #+#             */
/*   Updated: 2022/09/12 21:22:21 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 이상한게 있는지 체크하는 함수
 *
 * @param input - 입력된 문자열
 * @param index - 문자열의 인덱스 위치
 * @param envp - 환경변수
 * @param c - 작은 따옴표나 큰따옴표나 공백
 * @return true - 있다면
 * @return false - 없다면
 */
t_bool	check_ambigu(char *input, int index, t_env *envp, char c)
{
	int	len;

	len = len_env(input + index, c);
	while (envp)
	{
		if (ft_strncmp(envp->str, input + index + 1, len - 1) == 0
			&& envp->str[len - 1] == '=')
			return (FALSE_E);
		envp = envp->next;
	}
	if (input[index + len] == '\0')
		return (TRUE_E);
	if (c == ' ' && (input[index + len] == ' ' || input[index + len] == '\0'))
		return (TRUE_E);
	if ((c == '"' || c == '\'') && (input[index + len] == c))
	{
		index++;
		if (input[index + len] == ' ' || input[index + len] == '\0')
			return (TRUE_E);
	}
	return (FALSE_E);
}

/**
 * @brief - 넘겨줘야할게 있는지 체크하는 함수
 *
 * @param input - 입력된 문자열
 * @param index - 입력된 문자열의 인덱스
 * @param envp - 환경변수
 * @return true - 있다면
 * @return false - 없다면
 */
t_bool	ambigu_redirect(char *input, int index, t_env *envp)
{
	skip_operator_space(input, &index);
	if (input[index] != '"' && input[index] != '\'' && input[index] != '$')
		return (FALSE_E);
	if (input[index] == '\0')
		return (FALSE_E);
	if (input[index] == '$')
		return (check_ambigu(input, index, envp, ' '));
	else if (input[index] == '"' && input[index + 1] == '$')
		return (check_ambigu(input, index + 1, envp, input[index]));
	return (FALSE_E);
}

/**
 * @brief 다른타입의 노드를 생성하고 초기화
 *
 * @param size - data의 길이
 * @return t_node*
 */
t_node	*create_ambigu_node(int size)
{
	t_node	*ret;

	ret = malloc(sizeof(t_node));
	if (ret == NULL)
		return (NULL);
	ret->arg = malloc(sizeof(char *) * 2);
	if (ret->arg == NULL)
	{
		free(ret);
		return (NULL);
	}
	ret->arg[0] = malloc(sizeof(char) * size + 1);
	if (ret ->arg[0] == NULL)
	{
		free(ret->arg);
		free(ret);
		return (NULL);
	}
	ret->type = AMBIGU_E;
	ret->arg[1] = NULL;
	return (ret);
}

/**
 * @brief - 다른 경우의 노드 생성
 *
 * @param input - 입력된 문자열
 * @param index - 입력된 문자열에 대한 시작위치
 * @return t_node* 다른타입의 노드
 */
t_node	*set_ambigu(char *input, int *index)
{
	int		len;
	int		count;
	t_node	*ret;

	count = 0;
	skip_operator_space(input, index);
	if (input[*index] == '"' || input[*index] == '\'')
		*index += 1;
	len = len_env(input + *index + 1, ' ');
	ret = create_ambigu_node(len + 1);
	if (ret == NULL)
		return (null_err("Allocation failure error in set ambigu"));
	while (count <= len)
	{
		ret->arg[0][count] = input[*index];
		count++;
		*index += 1;
	}
	ret->arg[0][count] = '\0';
	if (input[*index] == '"' || input[*index] == '\'')
		*index += 1;
	while (is_space(input[*index]) == TRUE_E)
		*index += 1;
	return (ret);
}
