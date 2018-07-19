/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 14:39:10 by alikhtor          #+#    #+#             */
/*   Updated: 2018/07/16 14:39:13 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void ft_allocate_memory_for_next_room(t_lem *g)
{
    g->room->next = (t_rooms*)malloc(sizeof(t_rooms));
    ft_bzero(g->room->next, sizeof(t_rooms));
}

static int  ft_check_start_or_end(t_lem *g)
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
    ft_allocate_memory_for_next_room(g);
    return (0);
}

static int  ft_start_or_end(t_lem *g)
{
    int     l;
    int     i;
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
    if (space != 2)
        return (1);
    if (ft_check_start_or_end(g))
        return (1);
    return (0);
}

int 		ft_start(t_lem *g)
{
    g->input = g->input->next;
    g->flag_start += 1;
    if (g->flag_start > 1)
        return (ft_error(22));
    if (g->input->data[0] == 'L' || g->input->data[0] == '#')
        return (ft_error(4));
    if (g->input->next == NULL)
        return (ft_error(2));
    if (ft_start_or_end(g))
        return (ft_error(551));
    ft_strdel(&g->room->type);
    ft_add_room_type(g, "start");
    g->room = g->room->next;
    return (0);
}

int 		ft_end(t_lem *g)
{
    g->input = g->input->next;
    g->flag_end += 1;
    if (g->flag_end > 1)
        return (ft_error(33));
    if (g->input->data[0] == 'L' || g->input->data[0] == '#')
        return (ft_error(4));
    if (g->input->next == NULL)
        return (ft_error(3));
    if (ft_start_or_end(g))
        return (ft_error(552));
    ft_strdel(&g->room->type);
    ft_add_room_type(g, "end");
    g->room = g->room->next;
    return (0);
}
