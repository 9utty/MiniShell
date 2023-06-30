/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:28:14 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:22:22 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 문자열 긑에 문자를 넣는 함수(세그폴트가 없는경우)
 *
 * @param str
 * @param c
 */
static void	add_char_to_str(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	if (c)
		str[index] = c;
	str[index + 1] = '\0';
}

/**
 * @brief - 모든 문자열과 문자를 차례대로 합쳐서 STDERR에 출력하는 함수
 *
 * @param str1
 * @param char1
 * @param char2
 * @param str2
 */
void	print_error_str_char(char *str1, char char1, char char2, char *str2)
{
	int		strlen;
	int		char_count;
	char	*error_message;

	char_count = 0;
	if (!str1 && !str2 && !char1 && !char2)
		return ;
	if (char1)
		char_count += 1;
	if (char2)
		char_count += 1;
	strlen = ft_strlen(str1) + char_count + ft_strlen(str2) + 1;
	error_message = ft_calloc(strlen, sizeof(char));
	if (!error_message)
	{
		write(STDERR_FILENO, "Malloc error\n", 14);
		return ;
	}
	ft_strlcat(error_message, str1, strlen);
	add_char_to_str(error_message, char1);
	add_char_to_str(error_message, char2);
	ft_strlcat(error_message, str2, strlen);
	write(STDERR_FILENO, error_message, strlen);
	free(error_message);
}

/**
 * @brief - 모든 문자열을 합쳐서 STDERR에 출력하는 함수
 *
 * @param str1
 * @param str2
 * @param str3
 */
void	print_error_str(char *str1, char *str2, char *str3)
{
	int		strlen;
	char	*error_message;

	if (!str1 && !str2 && !str3)
		return ;
	strlen = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1;
	error_message = ft_calloc(strlen, sizeof(char));
	if (!error_message)
	{
		write(STDERR_FILENO, "Malloc error\n", 14);
		return ;
	}
	ft_strlcat(error_message, str1, strlen);
	ft_strlcat(error_message, str2, strlen);
	ft_strlcat(error_message, str3, strlen);
	write(STDERR_FILENO, error_message, strlen);
	free(error_message);
}

/**
 * @brief - STDERR에 메시지를 출력하고 NULL을 반환
 *
 * @param errmsg - 출력할 에러메시지
 * @return void*
 */
void	*null_err(char *errmsg)
{
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}

/**
 * @brief - STDERR에 errmsg를 출력하고 false를 반환
 *
 * @param errmsg - 출력할 에러메시지
 * @return t_bool
 */
t_bool	bool_err(char *errmsg)
{
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
	write(STDERR_FILENO, "\n", 1);
	return (FALSE_E);
}
