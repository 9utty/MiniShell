/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:10:23 by gulee             #+#    #+#             */
/*   Updated: 2022/09/14 14:51:17 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - pid리스트에서 첫번째 노드를 가져오는 함수
 *
 * @return t_ps_list* - 첫번째 노드
 */
t_ps_list	*get_first_pid_node(void)
{
	static t_ps_list	first;

	return (&first);
}

/**
 * @brief - pid리스트의 마지막 노드를 가져오기 위한 함수
 *
 * @return t_ps_list* - 마지막 pid노드
 */
t_ps_list	*get_last_pid_node(void)
{
	t_ps_list	*tmp;

	tmp = get_first_pid_node();
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/**
 * @brief - pid 리스트에 새로운 pid를 추가하기 위한 함수
 *
 * @param new_pid - 추가할 pid 노드
 * @return 0 - 성공
 * @return -1 - 할당 실패
 */
int	save_pid(pid_t new_pid)
{
	t_ps_list	*new;
	t_ps_list	*last;

	new = malloc(sizeof(t_ps_list));
	if (!new)
		return (-1);
	new->pid = new_pid;
	new->next = NULL;
	last = get_last_pid_node();
	last->next = new;
	return (0);
}

/**
 * @brief - t_ps_list 를 업데이트 하기 위한 함수
 *
 */
void	update_pid(void)
{
	t_ps_list	*tmp;
	t_ps_list	*next;

	tmp = get_first_pid_node();
	tmp = tmp->next;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	tmp = get_first_pid_node();
	tmp->next = NULL;
}

/**
 * @brief - 마지막 종료코드를 체크하고 업데이트하는 함수
 */
void	run_exit_set_code(void)
{
	t_ps_list	*node;
	t_ps_list	*last_child;
	int			return_wait;

	node = get_first_pid_node();
	last_child = get_last_pid_node();
	if (!node->next)
		return ;
	waitpid(last_child->pid, &return_wait, 0);
	while (node && node->next)
	{
		wait(NULL);
		node = node->next;
	}
	update_pid();
	if (!WIFSIGNALED (return_wait))
		get_global_data()->exitcode = WEXITSTATUS (return_wait);
	else if (WIFSIGNALED (return_wait) && get_global_data()->exitcode == 131)
		write(STDERR_FILENO, "Quit: 3\n", 9);
	else if (WIFSIGNALED (return_wait) && get_global_data()->exitcode == 130)
		printf("\n");
}
