/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:22:23 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:21:05 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - syntax error를 출력하기 위한 함수
 *
 * @param str - 오류가 포함된 문자열
 * @param i - 오류가 나온 문자열의 위치
 */
static void	write_syntax_error(char *str, int *i)
{
	int	char_count;
	int	j;

	j = *i;
	char_count = 0;
	while (str[j] && str[*i] == str[j])
	{
		char_count++;
		j++;
	}
	if (char_count > 1)
		print_error_str_char(get_err(TOKEN_ERR_E), str[*i], str[*i], "'\n");
	else if (char_count == 1)
		print_error_str_char(get_err(TOKEN_ERR_E), str[*i], 0, "'\n");
	else if (char_count == 0)
		write(STDERR_FILENO, get_err(NL_ERR_E), ft_strlen(get_err(NL_ERR_E)));
	get_global_data()->exitcode = 258;
}

/**
 * @brief - whitespace를 스킵하는 함수
 */
static void	skip_whitespace(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		*i += 1;
}

/**
 * @brief - \0, \, ", |, >, < 를 건너뛰기 위한 함수
 *
 * @param str - 특수문자들을 포함한 문자열
 * @param i - str의 인덱스
 */
static void	skip_till_special_char(char *str, int *i)
{
	while (str[*i] != '\0'
		&& str[*i] != '\''
		&& str[*i] != '"'
		&& str[*i] != '|'
		&& str[*i] != '>'
		&& str[*i] != '<')
		*i += 1;
}

/**
 * @brief 문자열에서 syntax error를 체크하는 함수
 *
 * @param str - 체크해야할 문자열
 * @param i - 해당 문자열의 위치의 인덱스
 * @return true - 문제잇네?
 * @return false - 통과
 */
static t_bool	check_for_error(char *str, int *i)
{
	if (str[*i] == '>' || str[*i] == '<')
	{
		*i += 1;
		if (str[*i] == str[*i - 1])
			*i += 1;
		skip_whitespace(str, i);
		if (str[*i] == '>' || str[*i] == '<' || \
			str[*i] == '|' || str[*i] == '\0')
		{
			write_syntax_error(str, i);
			return (TRUE_E);
		}
	}
	if (str[*i] == '|')
	{
		*i += 1;
		skip_whitespace(str, i);
		if (str[*i] == '|' || str[*i] == '\0')
		{
			write_syntax_error(str, i);
			return (TRUE_E);
		}
	}
	return (FALSE_E);
}

/**
 * @brief - 문자열이 syntax_error인지 체크하는 함수
 *
 * @param str - 체크할 문자열
 * @return true - 문제있네?
 * @return false - 통과
 */
t_bool	check_syntax_error(char *str)
{
	int	i;

	i = 0;
	skip_whitespace(str, &i);
	if (str[i] == '|')
	{
		write_syntax_error(str, &i);
		return (TRUE_E);
	}
	while (str[i])
	{
		skip_till_special_char(str, &i);
		if (str[i] == '\'' || str[i] == '"')
			skip_string(str, &i);
		else if (str[i])
		{
			if (check_for_error(str, &i))
				return (TRUE_E);
		}
	}
	return (FALSE_E);
}
