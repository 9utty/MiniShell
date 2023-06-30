/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:01:41 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:20:18 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 해당 경로가 디렉토리인지 확인하는 함수
 *
 * @param path - 경로를 담고 있는 문자열
 * @return true - 맞다면
 * @return false - 아니라면
 */
static t_bool	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (FALSE_E);
	if (S_ISDIR(path_stat.st_mode))
		return (TRUE_E);
	return (FALSE_E);
}

/**
 * @brief - execve함수의 에러를 표시하고 정상 종료코드로 종료하는 함수
 *
 * @param path - 실행할 경로를 담고 있는 문자열
 * @param error - execve가 설정한 에러 넘버
 * @return exit 126 - 지정된 경로
 * @return exit 127 - 기타 오류들
 */
static void	execve_error(char *path, int error)
{
	if (error == EACCES)
	{
		if (is_directory(path))
		{
			print_error_str("\033[0;31mminishell: ", path, \
			": is a directory\n\033[0m");
			exit (126);
		}
		else
			print_error_str("\033[0;31mminishell: ", path, \
			": Premission denied\n\033[0m");
	}
	else if (error == ENOENT)
		print_error_str("\033[0;31mminishell: ", path, \
		": command not found\n\033[0m");
	else
		print_error_str("\033[0;31mminishell: ", path, \
		": execve error\n\033[0m");
	exit (127);
}

/**
 * @brief - execve를 호출하고 실행하는 함수
 *
 * @param arguments - execve에 전달해줄 모든 내용을 가지고 있는 이중배열
 * @param list - 환경변수 리스트
 * @return 0 - 성공시
 * @return -1 - 할당실패 / execve 실패
 * @return exit 127 - 명령어를 찾을 수 없을때
 */
int	execute_cmd(char **arguments, t_env *list)
{
	char	*execute_path;
	char	**env_array;

	execute_path = get_exec_path(arguments, list);
	if (!execute_path)
		exit (127);
	env_array = env_list_to_array(list);
	if (!env_array)
	{
		free(execute_path);
		return (return_erremsg("Malloc failed\n", NULL, NULL, -1));
	}
	if (execve(execute_path, arguments, env_array) == -1)
		execve_error(execute_path, errno);
	return (0);
}
