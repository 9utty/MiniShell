/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:45:29 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:55:46 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - -n 플래그인지 확인하는 함수
 *
 * @param str - 확인할 문자열
 * @return true - 있따!
 * @return false - 없따!
 */
static t_bool	is_n_flag(char *str)
{
	int	index;

	if (!str)
		return (FALSE_E);
	if (str[0] != '-')
		return (FALSE_E);
	index = 1;
	while (str[index])
	{
		if (str[index] != 'n')
			return (FALSE_E);
		index++;
	}
	return (TRUE_E);
}

/**
 * @brief - 인자의 내용을 STDOUT에 출력하는 함수
 * 			-n 옵션이 있다면 '\n'을 출력하지 않는다
 *
 * @param args - 출력할 인자의 내용을 가지고 있는 이중 배열
 */
void	echo(char **args)
{
	t_bool	newline;
	int		index;

	index = 0;
	newline = TRUE_E;
	get_global_data()->exitcode = 0;
	if (args[0] && is_n_flag(args[0]))
	{
		newline = FALSE_E;
		while (is_n_flag(args[index]))
			index++;
	}
	while (args[index])
	{
		write(1, args[index], ft_strlen(args[index]));
		index++;
		if (args[index])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
}
