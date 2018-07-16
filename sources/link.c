/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:20:18 by alikhtor          #+#    #+#             */
/*   Updated: 2018/07/16 17:20:20 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int  ft_work_with_link(t_lem *g, int flag_minus, size_t l, size_t ml)
{
    if (flag_minus != 1)
        return (ft_error(66));
    g->link->current = ft_strnew(ml);
    g->link->current = ft_memcpy(g->link->current, g->input->data, ml);
    g->link->following = ft_strnew((size_t)l - ml);
    g->link->following = ft_memcpy(g->link->following, g->input->data + (ml + 1), (size_t)l - (ml + 1));
    if (ft_strequ(g->link->current, "") || ft_strequ(g->link->following, ""))
        return (ft_error(66));
    g->link->next = (t_links*)malloc(sizeof(t_links));
    g->link = g->link->next;
    g->link->next = NULL;
    return (0);
}

int 		ft_link(t_lem *g)
{
    int     flag_minus;
    size_t  len;
    size_t  medium_len;

    flag_minus = 0;
    len = 0;
    medium_len = 0;
    while (g->input->data[len] != '\0')
    {
        if (!(ft_isprint(g->input->data[len])))
            return (ft_error(66));
        if (g->input->data[len] == '-')
        {
            medium_len = (size_t)len;
            flag_minus++;
        }
        len++;
    }
    return (ft_work_with_link(g, flag_minus, len, medium_len));
}