/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:55:14 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:07:46 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 명령어 또는 파이프를 찾을때까지 노드를 제거하는 함수
 *
 * @param node - 명령어 리스트
 */
void	set_till_cmd_pipe(t_node **node)
{
	while (node && (*node) && (*node)->type != TOSTDOUT_E \
			&& (*node)->type != PIPE_E)
		del_cmd_node(node);
}

/**
 * @brief - 파이프가 나올때까지 노드를 제거하는 함수
 *
 * @param node - 명령어 리스트
 */
void	set_next_pipe(t_node **node)
{
	while (node && *node && (*node)->type != PIPE_E)
		del_cmd_node(node);
	if (node && *node && (*node)->type == PIPE_E)
		del_cmd_node(node);
}

/**
 * @brief - 파이프가 있는지 체크하는 함수
 *
 * @param node - 명령어 리스트
 * @return true - 있으면
 * @return false - 없으면
 */
t_bool	is_pipe(t_node *node)
{
	while (node)
	{
		if (node->type == PIPE_E)
			return (TRUE_E);
		node = node->next;
	}
	return (FALSE_E);
}

/**
 * @brief - 명령어들에서 빌트인만 있는지 체크
 *
 * @param node - 명령어 리스트
 * @return true - 빌트인만 있다면
 * @return false - 없다면
 */
t_bool	only_builtin(t_node *node)
{
	while (node && node->type != PIPE_E)
	{
		if (node->type == TOSTDOUT_E
			&& !((ft_strncmp(node->arg[0], "cd", 3) == 0)
				|| (ft_strncmp(node->arg[0], "echo", 5) == 0)
				|| (ft_strncmp(node->arg[0], "env", 4) == 0)
				|| (ft_strncmp(node->arg[0], "exit", 5) == 0)
				|| (ft_strncmp(node->arg[0], "export", 7) == 0)
				|| (ft_strncmp(node->arg[0], "pwd", 4) == 0)
				|| (ft_strncmp(node->arg[0], "unset", 6) == 0)))
			return (FALSE_E);
		node = node->next;
	}
	return (TRUE_E);
}

/**
 * @brief - 경로를 복사하는 함수
 *
 * @param argument - 실행 경로
 * @return char* - 성공시
 * @return exit 1 - 할당실패
 */
char	*cpy_path(char *argument)
{
	char	*cmd_path;

	cmd_path = ft_strdup(argument);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "Malloc failed\n", 15);
		exit (1);
	}
	return (cmd_path);
}
