/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:49:59 by gulee             #+#    #+#             */
/*   Updated: 2022/09/01 15:56:21 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strncmp(const char *str1, const char *str2, size_t size)
{
	size_t	index;

	index = 0;
	if (size == 0)
		return (0);
	while ((index < size - 1) && (str1[index] != '\0') \
		&& (str2[index] != '\0') && str1[index] == str2[index])
		index++;
	return ((unsigned char)str1[index] - (unsigned char)str2[index]);
}
