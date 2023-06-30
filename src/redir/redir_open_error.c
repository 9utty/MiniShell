/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_open_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:51:07 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:20:22 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief 해당하는 오류구문 출력하는 함수
 *
 * @param path - 오류를 만든 경로를 담고 있는 문자열
 * @param error - error num
 * @return int
 */
int	open_error(char *path, int error)
{
	get_global_data()->exitcode = 1;
	if (error == EACCES)
		print_error_str("minishell: ", path, \
		": Premission denied\n");
	else if (error == EISDIR)
		print_error_str("minishell: ", path, \
		": Is a directory\n");
	else if (error == ENOENT)
		print_error_str("minishell: ", path, \
		": No such file or directory\n");
	else
		print_error_str("minishell: ", path, \
		": open error\n");
	return (-1);
}
