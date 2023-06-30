/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:12:41 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 19:02:11 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 현재 str 앞뒤에 공백이 있는지 체크하는 함수
 *
 * @param str - 체크할 문자열
 * @param index - 체크해야하는 인덱스
 * @return true - 공백이 없고
 * @return false - 없어진 공백도 없다
 */
static t_bool	miss_space(char *str, int index)
{
	if (index != 0 && str[index] && str[index - 1] != ' '
		&& ((str[index] == '<' && str[index - 1] != '<')
			|| (str[index] == '>' && str[index - 1] != '>')
			|| (str[index] == '|')))
		return (TRUE_E);
	if (index != 0 && str[index] && str[index] != ' '
		&& ((str[index - 1] == '>' && str[index] != '>')
			|| (str[index - 1] == '<' && str[index] != '<')
			|| (str[index - 1] == '|')))
		return (TRUE_E);
	return (FALSE_E);
}

/**
 * @brief 없어진 공백의 카운트를 리턴하는 함수
 *
 * @param str - 체크할 문자열
 * @return int - 카운트 반환
 */
static int	get_miss_space(char *str)
{
	int	index;
	int	space;

	index = 0;
	space = 0;
	while (str[index])
	{
		if (!in_str(str[index], FALSE_E) && miss_space(str, index))
			++space;
		++index;
	}
	in_str(str[index], TRUE_E);
	return (space);
}

/**
 * @brief - input을 output으로 복사하는 함수
 * 			필요한 곳에 공백을 추가
 *
 * @param input - 입력받은 문자열
 * @param output - 보내야할 문자열
 */
static void	fill_out(char *input, char *output)
{
	int	index;
	int	j;

	index = 0;
	j = 0;
	while (input[index])
	{
		if (!in_str(input[index], FALSE_E) && miss_space(input, index))
		{
			output[j] = ' ';
			j++;
		}
		output[j] = input[index];
		++j;
		++index;
	}
	in_str(input[index], TRUE_E);
	output[j] = '\0';
}

/**
 * @brief - 토큰화를 하는 함수 syntax error도 확인한다
 *
 * @param input - 가공처리전 문자열
 * @return char* -
 * 					NULL - syntax error / malloc failed
 * 					output - 잘 가공된 문자열
 */
char	*lexer(char	*input)
{
	int		space;
	char	*output;

	if (check_syntax_error(input))
	{
		free(input);
		return (NULL);
	}
	space = get_miss_space(input);
	output = malloc(sizeof(char) * (ft_strlen(input) + space + 1));
	if (!output)
	{
		write(STDERR_FILENO, "Malloc failed\n", 15);
		free(input);
		return (NULL);
	}
	fill_out(input, output);
	free(input);
	return (output);
}
