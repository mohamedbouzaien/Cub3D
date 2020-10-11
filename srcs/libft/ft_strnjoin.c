/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 00:01:23 by mbouzaie          #+#    #+#             */
/*   Updated: 2020/10/11 15:11:14 by mbouzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char			*ft_strnjoin(const char *s1, const char *s2, int len)
{
	char	*s;
	char	*ret;

	if (len == -1)
		len = 0;
	if (!(s = ft_strnew(ft_chrloc(s1, '\0') + len)))
		return (NULL);
	ret = s;
	while (s1 && *s1)
		*s++ = *s1++;
	while (*s2 && s2 && len--)
		*s++ = *s2++;
	*s = '\0';
	return (ret);
}
