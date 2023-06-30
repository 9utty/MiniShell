/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:58:18 by gulee             #+#    #+#             */
/*   Updated: 2022/09/12 20:36:30 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief 환경변수 확장 후 문자열의 총 길이를 반환하는 함수
 *
 * @param input - 환경변수가 있는 문자열에 대한 포인터
 * @param env - 환경변수
 * @return int - 확장 후 길이
 */
static int	get_total_str_len(char *input, t_env *env)
{
	int	len;
	int	index;

	index = 0;
	len = 0;
	while (input[index])
	{
		if (input[index] == '$' && input[index + 1] != ' ')
		{
			index += len_env_str(&input[index], '\0', &len, env);
			continue ;
		}
		len++;
		index++;
	}
	return (len);
}

/**
 * @brief - heredoc의 입력 라인을 환경변수로 확장하는 함수
 *
 * @param input - heredoc 에 입력된걸 포함하는 이중배열
 * @param type - heredoc 의 타입 (따옴표가 있다면 환경변수 확장)
 * @param env - 환경변수
 * @return int - 0 성공 -1 할당실패
 */
int	expand_hdoc(char **input, int type, t_env *env)
{
	char	*new_str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (type == HDOCQUOTE_E)
		return (0);
	new_str = ft_calloc(get_total_str_len((*input), env) + 1, sizeof(char));
	if (!new_str)
		return (-1);
	while ((*input)[i])
	{
		if ((*input)[i] == '$' && (*input)[i + 1] != ' ')
		{
			i += in_env_till_sapce(&new_str[count], &(*input)[i], env, &count);
			continue ;
		}
		new_str[count] = (*input)[i];
		i++;
		count++;
	}
	free(*input);
	*input = new_str;
	return (0);
}

/**
 * @brief - 사용자에게 입력받은 값을 파일에 입력하는 함수
 *
 * @param heredoc_path heredoc 파일의 경로입니다.
 *
 * @param delimiter heredoc 구분 기호를 포함하는 문자열에 대한 포인터.
 *
 * @param type heredoc의 유형(확장 유무에 관계없이).
 *
 * @param env 환경 변수 목록에 대한 포인터.
 *
 * @return - [0] 성공 - [-1] 신호 중단 / heredoc 실패 -
*/
void	input_to_hdoc(const char *heredoc_path, \
						char *delimiter, int type, t_env *env)
{
	int		fd;
	char	*in;

	in = NULL;
	fd = open(heredoc_path, O_WRONLY | O_TRUNC);
	if (fd == -1)
		exit (-1);
	while (1)
	{
		in = readline("> ");
		if (!in)
			exit (close_fd_free(fd, delimiter, NULL, 0));
		if (ft_strcmp(delimiter, in) == 0)
			exit (close_fd_free(fd, delimiter, in, 0));
		if (expand_hdoc(&in, type, env) == -1)
			exit (close_fd_free(fd, delimiter, in, -1));
		else if (write(fd, in, ft_strlen(in)) == -1 || write(fd, "\n", 1) == -1)
			exit (close_fd_free(fd, delimiter, in, -1));
		free(in);
	}
}
