/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 20:27:13 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/05/12 18:52:30 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_intlength(int n)
{
	int len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len = 1;
		n = -n;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*ito;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (!(ito = (char *)malloc(sizeof(char) * (ft_intlength(n) + 1))))
		return (NULL);
	i = ft_intlength(n) - 1;
	ito[i + 1] = '\0';
	if (n < 0)
	{
		ito[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		ito[i] = (n % 10) + 48;
		i--;
		n /= 10;
	}
	return (ito);
}
