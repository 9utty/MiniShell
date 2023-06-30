/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:07:32 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:18:29 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 명령어를 확인 후 해당하는 명령어를 실행하는 함수
 *
 * @param table - 글로벌구조체
 * @return true - 정상 실행
 * @return false - 못찾아서 실행못할 경우
 * @return exit - export 호출 후 실패한 경우
 */
t_bool	run_builtin_child(t_table table)
{
	int	return_value;

	return_value = 0;
	if (ft_strncmp((*table.node_head)->arg[0], "cd", 3) == 0)
		return_value = cd(&(*table.node_head)->arg[1], table.env_head);
	else if (ft_strncmp((*table.node_head)->arg[0], "echo", 5) == 0)
		echo(&(*table.node_head)->arg[1]);
	else if (ft_strncmp((*table.node_head)->arg[0], "env", 4) == 0)
		env((*table.env_head));
	else if (ft_strncmp((*table.node_head)->arg[0], "exit", 5) == 0)
		exit_shell(&(*table.node_head)->arg[1], FALSE_E);
	else if (ft_strncmp((*table.node_head)->arg[0], "export", 7) == 0)
		return_value = export(&(*table.node_head)->arg[1], table.env_head);
	else if (ft_strncmp((*table.node_head)->arg[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp((*table.node_head)->arg[0], "unset", 6) == 0)
		unset(&(*table.node_head)->arg[1], table.env_head);
	else
		return (FALSE_E);
	if (return_value != 0)
		exit (1);
	return (TRUE_E);
}

/**
 * @brief - 빌트인 명령어를 가지고 있는 노드가 나올때까지 지우는 함수
 *
 * @param node - 명령어리스트
 * @param list - 환경변수리스트
 * @return 0 - 빌트인을 찾을 수 없는 경우
 * @return -1 - 문제가 생긴경우
 */
int	run_builtin_no_pipe(t_node **node, t_env **list)
{
	int		return_value;

	return_value = 0;
	set_till_cmd_pipe(node);
	if (!node || !*node)
		return (0);
	if (ft_strncmp((*node)->arg[0], "cd", 3) == 0)
		return_value = cd(&(*node)->arg[1], list);
	else if (ft_strncmp((*node)->arg[0], "echo", 5) == 0)
		echo(&(*node)->arg[1]);
	else if (ft_strncmp((*node)->arg[0], "env", 4) == 0)
		env(*list);
	else if (ft_strncmp((*node)->arg[0], "exit", 5) == 0)
		exit_shell(&(*node)->arg[1], TRUE_E);
	else if (ft_strncmp((*node)->arg[0], "export", 7) == 0)
		return_value = export(&(*node)->arg[1], list);
	else if (ft_strncmp((*node)->arg[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp((*node)->arg[0], "unset", 6) == 0)
		unset(&(*node)->arg[1], list);
	if (return_value == -1)
		return (-1);
	return (0);
}
