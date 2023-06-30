/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:02:10 by gulee             #+#    #+#             */
/*   Updated: 2022/09/09 00:41:05 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	len;

	len = ft_strlen(s1);
	if (len < ft_strlen(s2))
		len = ft_strlen(s2);
	return (ft_memcmp(s1, s2, len));
}

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			count;
	size_t			index;

	str1 = (unsigned char *)ptr1;
	str2 = (unsigned char *)ptr2;
	count = num;
	index = 0;
	while (count)
	{
		if (str1[index] != str2[index])
			return (str1[index] - str2[index]);
		index++;
		count--;
	}
	return (0);
}
