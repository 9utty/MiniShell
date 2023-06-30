/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 02:52:10 by gulee             #+#    #+#             */
/*   Updated: 2022/09/01 14:13:22 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_num_lenth(int nb)
{
	size_t	lenth;

	lenth = 0;
	if (nb <= 0)
		lenth++;
	while (nb)
	{
		lenth++;
		nb = (nb / 10);
	}
	return (lenth);
}

char	*ft_itoa(int n)
{
	long long	tmp;
	size_t		lenth;
	char		*str;

	lenth = ft_num_lenth(n);
	tmp = n;
	str = NULL;
	str = malloc(sizeof(char) * lenth + 1);
	if (str == NULL)
		return (NULL);
	if (tmp < 0)
	{
		str[0] = '-';
		tmp = tmp * -1;
	}
	if (tmp == 0)
		str[0] = '0';
	str[lenth--] = '\0';
	while (tmp)
	{
		str[lenth] = (tmp % 10) + '0';
		tmp = tmp / 10;
		lenth--;
	}
	return (str);
}
