/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:42:47 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:00:48 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 문자열을 새로 할당된 하나의 문자열로 연결하는 함수
 * 			원래 있던 문자열은 그대로 냅둠
 *
 * @param var - 작업디렉토리 앞에 있어야할 내용
 * @param pwd - 작업디렉토리의 경로를 가지고 있는 문자열
 * @return char* - 새로 만든 문자열
 */
char	*create_new_cd_str(char *var, char *pwd)
{
	int		strlen_pwd;
	int		strlen_var;
	int		new_str_size;
	char	*new;

	strlen_pwd = ft_strlen(pwd);
	strlen_var = ft_strlen(var);
	new_str_size = strlen_pwd + strlen_var + NULL_E;
	new = ft_calloc(new_str_size, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcat(new, var, new_str_size);
	ft_strlcat(new, pwd, new_str_size);
	return (new);
}

/**
 * @brief - 환경변수 내의 PWD 노드의 내용을 현재 작업 디렉토리로
 * 			변경하는 함수
 * 			PWD 노드가 없으면 1을 반환
 *
 * @param env - 환경변수리스트
 * @return 0 - 성공
 * @return 1 - PWD노드가 없는 경우
 * @return -1 - 할당실패
 */
static int	change_pwd_path(t_env *env)
{
	t_env	*path;
	char	*new_pwd;
	char	*pwd;

	path = get_env_node(env, "PWD");
	if (!path)
		return (1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	new_pwd = create_new_cd_str("PWD=", pwd);
	free(pwd);
	if (!new_pwd)
		return (-1);
	free(path->str);
	path->str = new_pwd;
	return (0);
}

/**
 * @brief - PWD 노드의 내용을 가져와 OLDPWD 노드 내부에 설정하는 함수
 * 			PWD가 존재하지 않고 OLDPWD가 아직 비어 있지 않은 경우
 * 			OLWPWD 노드를 빈 문자열로 설정
 * 			OLDPWD가 비어 있고 PWD가 존재하지 않으면 마지막 작업 디렉토리로 설정
 *
 * @param env - 환경변수리스트
 * @param is_null - OLDPWD를 확인하고 NULL인지 보는 값
 * @return 0 - 성공
 * @return -1 - 할당실패
 */
static int	set_old_pwd_path(t_env *env, t_bool *is_null)
{
	t_env	*oldpwd;
	t_env	*newpwd;

	oldpwd = get_env_node(env, "OLDPWD");
	newpwd = get_env_node(env, "PWD");
	if (oldpwd && newpwd)
	{
		if (cpy_pwd_node(oldpwd, newpwd, is_null) == -1)
			return (-1);
	}
	else if (oldpwd && !newpwd && *is_null)
	{
		if (set_oldpwd(oldpwd) == -1)
			return (-1);
	}
	else if (oldpwd && !newpwd && !*is_null)
	{
		if (init_empty_old(oldpwd, is_null) == -1)
			return (-1);
	}
	return (0);
}

/**
 * @brief - 한번도 cd가 호출되지 않은 경우
 * 			OLDPWD가 있는걸 사용하거나 하나 만들어서 true 설정 후
 * 			빈문자열을 포함하는 함수
 *
 * @param start_of_program - 처음 호출인지 확인하는 불값
 * @param env - 환경변수 리스트
 * @return 0 - 성공
 * @return -1 - 할당 실패
 */
static int	first_cd_call(t_bool *start_of_program, t_env **env)
{
	t_env	*oldpwd;

	oldpwd = get_env_node(*env, "OLDPWD");
	if (*start_of_program == FALSE_E)
		return (0);
	*start_of_program = FALSE_E;
	if (oldpwd)
	{
		oldpwd->is_value = TRUE_E;
		free(oldpwd->str);
		oldpwd->str = ft_strdup("OLDPWD=");
		if (!oldpwd->str)
			return (-1);
	}
	else
	{
		if (init_new_old(env) == -1)
			return (-1);
	}
	return (0);
}

/**
 * @brief - 현재 작업 디렉토리를 바꾸는 함수
 *
 * @param argument - 실행할 모든 인자를 가지고 있는 이중 배열
 * @param env - 환경변수리스트
 * @return 0 - 성공
 * @return 1 - 실행 실패
 * @return -1 - 할당 실패
 */
int	cd(char **argument, t_env **env)
{
	static t_bool	is_null = FALSE_E;
	static t_bool	start_of_program = TRUE_E;
	t_env			*home_path;

	if (!*argument || argument[0][0] == '\0')
	{
		home_path = get_env_node(*env, "HOME");
		if (!home_path || home_path->is_value == FALSE_E)
			return (cd_home_path_not_set());
		else if (home_path->str[5] == '\0')
			return (0);
		else if (chdir(&home_path->str[5]) != 0)
			return (chdir_error(&home_path->str[5], errno));
	}
	else if (chdir(argument[0]) != 0)
		return (chdir_error(argument[0], errno));
	if (first_cd_call(&start_of_program, env) == -1
		|| set_old_pwd_path(*env, &is_null) == -1
		|| change_pwd_path(*env) == -1)
		return (-1);
	get_global_data()->exitcode = 0;
	return (0);
}
