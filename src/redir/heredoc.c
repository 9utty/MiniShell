/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:07:47 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:22:55 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - fd를 닫고 문자열을 해제하는 함수
 *
 * @param fd - 닫고자 하는 fd
 * @param str1 - 해제할 문자열
 * @param str2 - 해제할 문자열
 * @param return_v 이 함수가 반환해야 할 값
 * @return int
 */
int	close_fd_free(int fd, char *str1, char *str2, int return_v)
{
	if (fd > 0)
	{
		if (close(fd) == -1)
			exit_erremsg("close failed\n", NULL, NULL, 1);
	}
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (return_v);
}

/**
 * @brief - heredoc을 실행하고 오류를 처리하기위해 fork()를 실행하는 함수
 *
 * @param hdoc_path heredoc 파일의 경로
 *
 * @param remove heredoc 구분 기호를 포함하는 문자열에 대한 포인터
 *
 * @param type heredoc의 유형(확장 유무에 관계없이)
 *
 * @param env 환경 변수 목록에 대한 포인터
 *
 * @return - [0] 성공 - [-1] 신호 중단 / heredoc 실패 -
 */
static int	run_hdoc(const char *hdoc_path, \
						char *remove, int type, t_env *env)
{
	int	ret_hdoc;

	ret_hdoc = 0;
	get_global_data()->hdoc_break = FALSE_E;
	get_global_data()->hdoc_pid = fork();
	if (get_global_data()->hdoc_pid == -1)
		exit_erremsg("Fork failed\n", NULL, NULL, 1);
	else if (get_global_data()->hdoc_pid == 0)
		input_to_hdoc(hdoc_path, remove, type, env);
	else
	{
		free(remove);
		signal(SIGINT, hdoc_handler);
		waitpid(get_global_data()->hdoc_pid, &ret_hdoc, 0);
		ret_hdoc = WEXITSTATUS (ret_hdoc);
		if (get_global_data()->hdoc_break == TRUE_E || ret_hdoc != 0)
			return (-1);
		init_signals();
	}
	return (0);
}

/**
 * @brief - heredoc에 있는 파일을 삭제하는 함수
 *
 * @param files - heredoc head의 포인터
 */
void	del_hdoc_file(t_hdoc **files)
{
	t_hdoc	*next;

	if (!files || !*files)
		return ;
	while (*files)
	{
		next = (*files)->next;
		if ((*files)->path)
		{
			unlink((*files)->path);
			free((*files)->path);
		}
		free(*files);
		*files = next;
	}
}

/**
 * @brief - heredoc을 처리하는 함수
 * 			쓸 파일을 생성하고 터미널에서 사용자 입력을 기다린다
 * @param node - 현재 작업에 대한 노드
 * @param file_paths - heredoc헤드의 대한 포인터
 * @param env - 환경변수
 * @return int
 * 			0 - 성공시
 * 			-1 - 오류
 */
int	heredoc(t_node *node, t_hdoc **file_paths, t_env *env)
{
	char	*remove;

	while (node)
	{
		if (node->type == HDOCSPACE_E || node->type == HDOCQUOTE_E)
		{
			remove = ft_strdup(node->arg[0]);
			if (!remove)
				return (-1);
			if (init_hdoc_file(node, file_paths) == -1)
			{
				free(remove);
				return (-1);
			}
			if (run_hdoc(node->arg[0], remove, \
							node->type, env) == -1)
				return (-1);
		}
		node = node->next;
	}
	return (0);
}
