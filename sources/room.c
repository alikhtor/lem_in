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

static int  ft_check_for_negative_integer(t_lem *g, int i)
{
    if (g->input->data[i + 1] == '-')
    {
        if (!(ft_isdigit(g->input->data[i + 2])))
            return (ft_error(55));
    }
    else if (!(ft_isdigit(g->input->data[i + 1])))
        return (ft_error(55));
    return (0);
}

static int  ft_check_integer_coordinate(t_lem *g, int *i)
{
    while (g->input->data[*i])
    {
        if (g->input->data[*i] == ' ' || g->input->data == '\0')
            break ;
        if (!(ft_isdigit(g->input->data[*i])))
            return (ft_error(773));
        *i = *i + 1;
    }
    return (0);
}

static int  ft_write_room_data(t_lem *g, int i)
{
    g->room->name = ft_strnew((size_t)i);
    g->room->name = ft_memcpy(g->room->name, g->input->data, (size_t) i);
    if (ft_check_for_negative_integer(g, i))
        return (1);
    g->room->x = ft_atoi(g->input->data + i + 1);
    if (g->input->data[i + 1] == '-')
        i++;
    i++;
    if (ft_check_integer_coordinate(g, &i))
        return (1);
    if (ft_check_for_negative_integer(g, i))
        return (1);
    g->room->y = ft_atoi(g->input->data + i);
    if (g->input->data[i + 1] == '-')
        i++;
    i++;
    if (ft_check_integer_coordinate(g, &i))
        return (1);
    return (0);
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
            if (ft_write_room_data(g, i))
                return (1);
            break ;
        }
    }
    ft_add_room_type(g, "");
    g->room->next = (t_rooms*)malloc(sizeof(t_rooms));
    ft_bzero(g->room->next, sizeof(t_rooms));
    return (2);
}