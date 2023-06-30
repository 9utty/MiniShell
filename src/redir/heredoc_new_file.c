/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_new_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:59:17 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:24:33 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - 주어진 unsigned long을 문자열에 배치된 16진수로 변환하는 함수
 *
 * @param num - 16진수로 변환할 정수
 * @return char* - 16진수를 포함하는 문자열을 반환
 * @return NULL - 할당실패시
 */
static char	*get_hex_value(unsigned long num)
{
	char	*str;
	int		index;

	index = 11;
	str = ft_calloc(13, sizeof(char));
	if (!str)
		return (NULL);
	while (num > 0)
	{
		if (num % 16 < 10)
			str[index] = num % 16 + '0';
		else
			str[index] = num % 16 + 'a' - 10;
		num /= 16;
		index--;
	}
	return (str);
}

/**
 * @brief - 임시 heredoc 파일을 위한 경로를 생성하고
 * 			heredoc 노드로 설정하는 함수
 *
 * @param heredoc_node - heredoc의 경로를 가지고 있는 노드
 * @return int - 0 경로설정성공 -1 할당실패
 */
static int	set_hdoc_in_node(t_node *heredoc_node)
{
	char	*path;
	char	*pointer_address;

	path = ft_calloc(39, sizeof(char));
	if (!path)
		return (-1);
	pointer_address = get_hex_value((unsigned long)heredoc_node->arg[0]);
	if (!pointer_address)
	{
		free(path);
		return (-1);
	}
	ft_strlcat(path, "/tmp/.minishell_heredoc0x", 39);
	ft_strlcat(path, pointer_address, 39);
	free(pointer_address);
	free(heredoc_node->arg[0]);
	heredoc_node->arg[0] = path;
	return (0);
}

/**
 * @brief - 주어진 경로를 포함하는 새 노드를 heredoc 연결 목록에 추가하는 함수
 *
 * @param filepaths - heredoc의 헤드포인터
 * @param new_path - 새 경로에 대한 포인터
 * @return int - 0 성공시 -1 할당실패시
 */
static int	add_hdoc_path(t_hdoc **filepaths, char *new_path)
{
	t_hdoc	*new;
	t_hdoc	*tmp;

	new = malloc(sizeof(t_hdoc) * 1);
	if (!new)
		return (-1);
	new->next = NULL;
	new->path = ft_strdup(new_path);
	if (!new->path)
	{
		free(new);
		return (-1);
	}
	tmp = *filepaths;
	if (!tmp)
	{
		*filepaths = new;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

/**
 * @brief - heredoc 파일을 생성하고 heredoc 연결 목록에 경로를
 * 			추가하는 기능
 *			파일 이름은 뒤에 추가된 구분 기호의 포인터 값과 함께
 *			".minishell_heredoc"이 된다
 *
 * @param heredoc_node - 구분자를 포함하는 작업 노드의 포인터
 * @param file_paths - heredoc head의 포인터
 * @return int - 0 성공시 -1 할당실패
 */
int	init_hdoc_file(t_node *heredoc_node, t_hdoc **file_paths)
{
	int	fd;

	if (set_hdoc_in_node(heredoc_node) == -1)
		return (-1);
	fd = open(heredoc_node->arg[0], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (-1);
	if (close(fd) == -1)
		exit_erremsg("close failed\n", NULL, NULL, 1);
	if (add_hdoc_path(file_paths, heredoc_node->arg[0]) == -1)
	{
		unlink(heredoc_node->arg[0]);
		return (-1);
	}
	return (0);
}
