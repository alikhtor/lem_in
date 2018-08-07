/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:42:23 by alikhtor          #+#    #+#             */
/*   Updated: 2017/11/10 12:22:54 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	size_t	len;
	size_t	i;

	if (s && f)
	{
		len = ft_strlen(s);
		res = (char*)malloc(sizeof(char) * (len + 1));
		if (res == 0)
			return (0);
		i = 0;
		while (i < len)
		{
			res[i] = f(s[i]);
			i++;
		}
		res[i] = 0;
		return (res);
	}
	return (0);
}
