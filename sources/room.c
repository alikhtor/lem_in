/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:14:51 by alikhtor          #+#    #+#             */
/*   Updated: 2018/07/16 17:14:53 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		ft_add_room_type(t_lem *g, char *room_type)
{
    if (ft_strequ(room_type, "start"))
        g->room->type = ft_strdup("start");
    else if (ft_strequ(room_type, "end"))
        g->room->type = ft_strdup("end");
    else
        g->room->type = ft_strdup("room");
}

int         ft_room(t_lem *g)
{
    int     i;
    int     line_len;

    i = -1;
    line_len = (int)ft_strlen(g->input->data);
    while (++i < line_len)
    {
        if (g->input->data[i] == ' ')
        {
            g->room->name = ft_strnew((size_t)i);
            g->room->name = ft_memcpy(g->room->name, g->input->data, (size_t) i);
            if (!(ft_isdigit(g->input->data[i + 1])))
                return (ft_error(55));
            g->room->x = ft_atoi(g->input->data + i + 1);
            i++;
            while (ft_isdigit(g->input->data[i]))
                i++;
            if (!(ft_isdigit(g->input->data[i + 1])))
                return (ft_error(55));
            g->room->y = ft_atoi(g->input->data + i);
            break;
        }
    }
    ft_add_room_type(g, "");
    g->room->next = (t_rooms*)malloc(sizeof(t_rooms));
    return (2);
}