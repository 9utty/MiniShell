/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:31:45 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:28:04 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 연산자 뒤에 오는 공백을 건너뛰는 함수
 *
 * @param input - 입력된 문자열
 * @param index - 반복하는 위치
 */
void	skip_operator_space(char *input, int *index)
{
	while (is_space(input[*index]) == FALSE_E)
		*index += 1;
	while (is_space(input[*index]) == TRUE_E)
		*index += 1;
}

/**
 * @brief - 파일 노드 생성
 *
 * @param len - 문자열의 길이
 * @param type - 노드의 type
 * @return t_node*
 */
t_node	*init_filenode(int len, int type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (null_err("Allocation failure error in filenode"));
	node->arg = malloc(sizeof(char *) * 2);
	if (node->arg == NULL)
	{
		free(node);
		return (null_err("Allocation failure error in filenode"));
	}
	*node->arg = malloc(sizeof(char) * len + 1);
	if (node->arg == NULL)
	{
		free(node->arg);
		free(node);
		return (null_err("Allocation failure error in filenode"));
	}
	node->arg[1] = NULL;
	node->type = type;
	node->next = NULL;
	return (node);
}

/**
 * @brief - redir 노드 만드는 함수
 *
 * @param input - 입력된 문자열
 * @param index - 입력된 문자열에 대한 반복 위치 포인터
 * @param type - 노드가 가지고 있어야 하는 type
 * @param envp - 환경변수
 * @return t_node*
 */
t_node	*set_redir_node(char *input, int *index, int type, t_env *envp)
{
	t_node	*node;
	int		len;

	len = 0;
	skip_operator_space(input, index);
	if (type == HDOC_E && (input[*index] == '\'' || input[*index] == '"'))
		type = HDOCQUOTE_E;
	else if (type == HDOC_E)
		type = HDOCSPACE_E;
	if (type == HDOCSPACE_E || type == HDOCQUOTE_E)
		read_hdoc(input + *index, &len);
	else
		read_input(input + *index, &len, envp);
	if (input[*index] == '\0' || is_operator(input[*index]) == TRUE_E)
		return (null_err("no string after space of redirect"));
	node = init_filenode(len, type);
	if (node == NULL)
		return (null_err("Allocation failure error in redir node"));
	if (type == HDOCSPACE_E || type == HDOCQUOTE_E)
		in_hdoc_out_str(*node ->arg, input, index);
	else
		in_str_out_node(*node ->arg, input, index, envp);
	return (node);
}

/**
 * @brief - file 노드의 타입을 정하는 함수
 *
 * @param input - lexer에서 작업이 완료된 문자열
 * @param index - input의 반복된 위치의 대한 포인터
 * @param envp - 환경 변수
 * @return t_node*
 */
t_node	*parser_file(char *input, int *index, t_env *envp)
{
	t_node	*node;

	node = NULL;
	if (str_end(input, *index, 2) != 2)
		return (null_err("no string after redirect"));
	if (!(input[*index] == '<' && input[*index + 1] == '<')
		&& ambigu_redirect(input, *index, envp) == TRUE_E)
		node = set_ambigu(input, index);
	else if (input[*index] == '<' && input[*index + 1] == ' ')
		node = set_redir_node(input, index, INFILE_E, envp);
	else if (input[*index] == '>' && input[*index + 1] == ' ')
		node = set_redir_node(input, index, TRUNC_E, envp);
	else if (input[*index] == '<' && input[*index + 1] == '<')
		node = set_redir_node(input, index, HDOC_E, envp);
	else if (input[*index] == '>' && input[*index + 1] == '>')
		node = set_redir_node(input, index, APPEND_E, envp);
	return (node);
}
