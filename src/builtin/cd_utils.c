/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:37:28 by gulee             #+#    #+#             */
/*   Updated: 2022/10/04 12:21:25 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

/**
 * cd 오류에 맞는 메시지 출력
 *
 * @param str 오류를 만든 명령어
 *
 * @return (1)
 */
int	chdir_error(char *str, int error)
{
	get_global_data()->exitcode = 1;
	if (error == EACCES)
		print_error_str("minishell: cd: ", str, \
								": Permission denied\n");
	else if (error == ENOENT)
		print_error_str("minishell: cd: ", str, \
								": No such file or directory\n");
	else if (error == ENOTDIR)
		print_error_str("minishell: cd: ", str, \
								": Not a directory\n");
	else
		print_error_str("minishell: cd: ", str, \
								": Change directory error\n");
	return (1);
}

/**
 * pwd_node의 내용을 복사하는 함수
 *
 * @param old_pwd가 있는 노드
 * @param pwd_node 복사해야할 노드
 *
 * @return 메모리 할당에 실패하면 (-1) 아니면 (0)
*/
int	cpy_pwd_node(t_env *oldpwd, t_env *pwd_node, t_bool *is_null)
{
	int	oldpwd_size;

	*is_null = FALSE_E;
	free(oldpwd->str);
	oldpwd->str = NULL;
	oldpwd_size = ft_strlen(pwd_node->str) + OLD_E + NULL_E;
	oldpwd->str = ft_calloc(oldpwd_size, sizeof(char));
	if (!oldpwd->str)
		return (-1);
	ft_strlcat(oldpwd->str, "OLD", oldpwd_size);
	ft_strlcat(oldpwd->str, pwd_node->str, oldpwd_size);
	return (0);
}

/**
 * old_pwd 를 설정하는 함수 현재 작업중인 dir(dir을 변경 전)
 *
 * @param oldpwd old_pwd에 대한 포인터
 *
 * @return - 성공시 (0) - 실패시 (-1)
 *
 */
int	set_oldpwd(t_env *oldpwd)
{
	char	*cwd;

	free(oldpwd->str);
	oldpwd->str = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	oldpwd->str = create_new_cd_str("OLDPWD=", cwd);
	free(cwd);
	if (!oldpwd->str)
		return (-1);
	return (0);
}

/**
 * old_pwd 노드 내용을 포함하는 함수 / 문자열은 비어있다.
 *
 * @param oldpwd old_pwd의 노드에 대한 포인터
 *
 * @param is_null old_pwd가 null인지 알려주는
 *
 * @return - 성공 (0) - 실패시 (-1)
*/
int	init_empty_old(t_env *oldpwd, t_bool *is_null)
{
	free(oldpwd->str);
	oldpwd->str = create_new_cd_str("OLDPWD=", NULL);
	oldpwd->is_value = TRUE_E;
	*is_null = TRUE_E;
	if (!oldpwd->str)
		return (-1);
	return (0);
}

/**
 * 새로운 환경 변수를 만드는 함수
 * "OLPWD=" 를 포함한다
 *
 * @param env env의 헤드의 주소이다
 *
 * @return - 성공 (0) - 실패 (-1)
*/
int	init_new_old(t_env **env)
{
	char	*old_pwd;

	old_pwd = ft_strdup("OLDPWD=");
	if (!old_pwd)
		return (-1);
	if (add_env_node(env, old_pwd) == -1)
	{
		free(old_pwd);
		return (-1);
	}
	return (0);
}
