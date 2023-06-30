/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:52:21 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:03:28 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - STDERR에 에러메시지를 출력하는 함수
 *
 * @param str - 에러를 만든 문자열
 * @return exit 255
 */
static void	exit_shell_error(char *str, t_bool print)
{
	if (print)
		write(STDERR_FILENO, "exit\n", 6);
	exit_erremsg("minishell: exit: ", str, \
		": numeric argument required\n", 255);
}

/**
 * @brief - 문자열을 long자료형으로 바꾸는 함수
 *
 * @param str - 변환할 문자열
 */
static int	ft_atol(char *str, t_bool print)
{
	size_t	tmp;
	ssize_t	return_value;
	int		sign;
	int		index;

	index = 0;
	tmp = 0;
	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		++index;
	}
	while (str[index])
	{
		tmp *= 10;
		tmp += str[index] - '0';
		++index;
		if (tmp > __LONG_LONG_MAX__ && \
			!(tmp - __LONG_LONG_MAX__ == 1 && sign == -1))
			exit_shell_error(str, print);
	}
	return_value = tmp * sign;
	return (return_value);
}

/**
 * @brief - 유효한지 체크하는 함수
 *
 * @param str - 체크할 인자를 가지고 있는 문자열
 * @return true - 유효하지 않다면
 * @return false - 정확하면
 */
static t_bool	check_valid_arg(char *str)
{
	int	index;

	index = 0;
	if (str[0] == '-' && str[1] != '\0')
		index++;
	while (str[index] && (str[index] >= '0' && str[index] <= '9'))
		index++;
	if (index >= 21 || str[index] != '\0')
		return (TRUE_E);
	return (FALSE_E);
}

/**
 * @brief - 글로벌구조체의 exitcode로 종료하는 함수
 */
static void	exit_global_code(t_bool print)
{
	if (print)
		write(STDERR_FILENO, "exit\n", 6);
	exit(get_global_data()->exitcode);
}

/**
 * @brief - 쉘을 종료하는 함수
 *
 * @param argument - exit에 들어갈 인수를 가지고 있는 이중 배열
 * @param print
 */
void	exit_shell(char **argument, t_bool print)
{
	size_t	arg;

	if (!argument)
		exit_global_code(print);
	if (count_string(argument) == 0)
	{
		if (print)
			write(STDERR_FILENO, "exit\n", 6);
		exit(0);
	}
	if (check_valid_arg(argument[0]))
		exit_shell_error(argument[0], print);
	if (count_string(argument) > 1)
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
		get_global_data()->exitcode = 1;
		return ;
	}
	arg = ft_atol(argument[0], print);
	if (print)
		write(STDERR_FILENO, "exit\n", 6);
	exit((int)arg);
}
