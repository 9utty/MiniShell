/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:59:02 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:23:52 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 명령어를 찾을 수 있는지 체크하는 함수
 *
 * @param path - 명령어 경로를 가지고 있는 문자열
 * @return true - 찾을 수 있는 경우
 * @return false - 찾을 수 없는 경우
 */
t_bool	check_get_cmd(const char *path)
{
	if (access(path, F_OK) == 0)
	{
		return (TRUE_E);
	}
	return (FALSE_E);
}

/**
 * @brief - 경로 사이에 "/"를 넣는 함수
 *
 * @param path - 경로를 가지고 있는 문자열
 * @param command - 실행할 것을 포함하는 문자열
 * @return char* - 다 만들어진 문자열 반환
 * @return NULL - 할당실패
 */
static char	*set_cmd_after_path(const char *path, const char *command)
{
	int		new_str_len;
	char	*new_str;

	new_str_len = ft_strlen(path) + ft_strlen(command) + 2;
	new_str = ft_calloc(new_str_len, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcat(new_str, path, new_str_len);
	ft_strlcat(new_str, "/", new_str_len);
	ft_strlcat(new_str, command, new_str_len);
	return (new_str);
}

/**
 * @brief - PATH 환경변수에서 실행을 찾는 함수
 *
 * @param argument - 실행이름 포함된 이중배열
 *
 * @param path - PATH를 가지고 있는 노드
 *
 * @return char * - 경로 반환
 * @return NULL - 실행파일이 없는경우
 */
static char	*get_cmd_path_util(char **arguments, t_env *path)
{
	char	**all_paths;
	char	*execute_path;
	int		index;

	index = 0;
	all_paths = ft_split(path->str + 5, ':');
	if (!all_paths)
		return (NULL);
	while (all_paths[index])
	{
		execute_path = set_cmd_after_path(all_paths[index], arguments[0]);
		if (!execute_path)
			break ;
		if (check_get_cmd(execute_path))
		{
			free_double_array(all_paths);
			return (execute_path);
		}
		free(execute_path);
		index++;
	}
	free_double_array(all_paths);
	return (cpy_path(arguments[0]));
}

/**
 * @brief - 환경변수리스트 내에서 PATH를 가져오는 함수
 *
 * @param arguments - 실행할 이름을 포함하는 이중배열
 * @param list - 환경변수 리스트
 * @return char* - 경로 반환
 * @return NULL - 환경변수 리스트에 없는경우
 */
static char	*get_cmd_path(char **arguments, t_env *list)
{
	t_env	*path;
	char	*empty_command;
	char	*path_not_set;

	path = get_env_node(list, "PATH=");
	if (!path)
	{
		path_not_set = ft_strdup(arguments[0]);
		if (!path_not_set)
			write(2, "Malloc failed\n", 15);
		return (path_not_set);
	}
	if (arguments[0][0] == '\0')
	{
		empty_command = ft_strdup("");
		if (!empty_command)
			write(STDERR_FILENO, "Malloc failed\n", 15);
		return (empty_command);
	}
	return (get_cmd_path_util(arguments, path));
}

/**
 * @brief - PATH에 있나 상대경로에 있나 무조건 실행 경로를 가져오는 함수
 *
 * @param args - 실행 파일의 이름을 포함하는 이중 배열
 * @param list - 환경변수 리스트
 * @return char* - 경로반환
 * @return NULL - 못 찾을 경우
 */
char	*get_exec_path(char **args, t_env *list)
{
	char	*cmd_path;
	int		index;

	index = 0;
	if (!args || !args[0])
		return (NULL);
	if (args[0][0] == '.' && args[0][1] == '\0')
	{
		write(STDERR_FILENO, get_err(DOT_ERR_E), ft_strlen(get_err(DOT_ERR_E)));
		exit (2);
	}
	while (args[0][index])
	{
		if (args[0][index] == '/')
			return (cpy_path(args[0]));
		index++;
	}
	cmd_path = get_cmd_path(args, list);
	return (cmd_path);
}
