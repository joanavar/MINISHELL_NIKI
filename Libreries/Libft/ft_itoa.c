/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:11:21 by camurill          #+#    #+#             */
/*   Updated: 2024/01/25 22:09:54 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nlen(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		n *= -1;
		count = 1;
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char	*easter_egg(int n)
{
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	return (0);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		index;
	int		count;

	if (n == -2147483648 || n == 0)
		return (easter_egg(n));
	index = 0;
	count = ft_nlen(n);
	str = malloc(count + 1);
	if (!str)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	str[count--] = '\0';
	while (n)
	{
		index = n % 10;
		n = n / 10;
		str[count] = index + '0';
		count--;
	}
	return (str);
}
