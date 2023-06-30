/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:03:35 by gulee             #+#    #+#             */
/*   Updated: 2022/09/09 19:19:18 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief - HOME의 경로가 없는 경우에 출력하는 함수
 *
 * @return int
 */
int	cd_home_path_not_set(void)
{
	get_global_data()->exitcode = 1;
	write(STDERR_FILENO, "minishell: cd: HOME not set\n", 29);
	return (0);
}
