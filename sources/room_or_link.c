/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_or_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:20:09 by alikhtor          #+#    #+#             */
/*   Updated: 2018/07/16 17:20:10 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static int  ft_room_or_link(t_lem *g)
{
    int     i;
    int     l;
    int     space;

    l = (int)ft_strlen(g->input->data);
    space = 0;
    i = -1;
    while (++i < l)
    {
        if (!(ft_isprint(g->input->data[i])))
            return (1);
        if (g->input->data[i] == ' ')
            space++;
    }
    if (space == 2)
        return (ft_room(g));
    else if (space == 0)
        return (ft_link(g));
    else
        return (1);
}


int         ft_room_or_link_or_comment(t_lem *g)
{
    int     todo;

    if (ft_strequ(g->input->data, "##start"))
    {
        if (ft_start(g))
            return (1);
    }
    else if (ft_strequ(g->input->data, "##end"))
    {
        if (ft_end(g))
            return (1);
    }
    else if (g->input->next != NULL)
    {
        if (g->input->data[0] != '#')
        {
            todo = ft_room_or_link(g);
            if (todo == 1)
                return (1);
            else if (todo == 2)
                g->room = g->room->next;
        }
    }
    return (0);
}