/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_return.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:05:20 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:05:19 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - fd를 닫고 에러메세지를 출력하는 함수
 *
 * @param error_messge - 출력할 에러메시지
 *
 * @param fd - 닫아야할 fd
 *
 * @param return_value - 실행 후 리턴할 값
 *
 * @return return_value - 성공
 * @return exit 1 - close failed
 *
 */
int	return_fd_close(char *error_message, int fd, \
		int return_value)
{
	if (close(fd) == -1)
		exit_erremsg("close failed\n", NULL, NULL, 1);
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	return (return_value);
}

/**
 * @brief - 프로그램을 종료하기전 사용하는 함수(종료하기전에 에러출력)
 *
 * @param str1 - 차례로 추가할 첫 번째 오류 문자열
 *
 * @param str2 - 차례로 추가할 두 번째 오류 문자열
 *
 * @param str3 - 차례로 추가할 마지막 오류 문자열
 *
 * @param exit_value - 종료하는데 사용할 값
 *
 */
void	exit_erremsg(char *str1, char *str2, char *str3, \
		int exit_value)
{
	int		strlen;
	char	*error_message;

	if (!str1 && !str2 && !str3)
		exit (exit_value);
	strlen = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	error_message = ft_calloc(strlen, sizeof(char));
	if (!error_message)
		exit (exit_value);
	ft_strlcat(error_message, str1, strlen);
	ft_strlcat(error_message, str2, strlen);
	ft_strlcat(error_message, str3, strlen);
	write(STDERR_FILENO, error_message, strlen);
	free(error_message);
	exit (exit_value);
}

/**
 * @brief - 반환할때 사용하는 함수(반환하기전에 error msg를 출력한다)
 *
 * @param str1 - 차례로 추가할 첫 번째 오류 문자열
 *
 * @param str2 - 차례로 추가할 두 번째 오류 문자열
 *
 * @param str3 - 차례로 추가할 마지막 오류 문자열
 *
 * @param return_value 반환하는 데 사용되는 값
 *
 */
int	return_erremsg(char *str1, const char *str2, char *str3, \
		int return_value)
{
	int		strlen;
	char	*error_message;

	if (!str1 && !str2 && !str3)
		return (return_value);
	strlen = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	error_message = ft_calloc(strlen, sizeof(char));
	if (!error_message)
		return (return_value);
	ft_strlcat(error_message, str1, strlen);
	ft_strlcat(error_message, str2, strlen);
	ft_strlcat(error_message, str3, strlen);
	write(STDERR_FILENO, error_message, strlen);
	free(error_message);
	return (return_value);
}
