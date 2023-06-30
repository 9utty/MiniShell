/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 02:34:27 by gulee             #+#    #+#             */
/*   Updated: 2022/09/09 00:42:46 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_bzero(void *ptr, size_t size)
{
	size_t			index;
	unsigned char	*sptr;

	index = 0;
	sptr = (unsigned char *)ptr;
	while (index < size)
	{
		sptr[index] = 0;
		index++;
	}
	ptr = sptr;
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = NULL;
	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
