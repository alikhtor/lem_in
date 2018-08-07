/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:16:12 by alikhtor          #+#    #+#             */
/*   Updated: 2017/11/02 17:17:52 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned char	*s1;
	size_t			i;

	s1 = (unsigned char*)s;
	i = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	return (i);
}
