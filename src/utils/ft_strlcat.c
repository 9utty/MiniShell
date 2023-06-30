/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:26:24 by gulee             #+#    #+#             */
/*   Updated: 2022/09/01 14:21:34 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	index;
	size_t	src_len;
	size_t	dest_len;

	index = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (size < dest_len + 1)
		return (size + src_len);
	if (size > dest_len + 1)
	{
		while ((src[index]) && ((dest_len + index + 1) < size))
		{
			dest[index + dest_len] = src[index];
			index++;
		}
	}
	dest[dest_len + index] = '\0';
	return (dest_len + src_len);
}
