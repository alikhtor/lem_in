/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_or_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:20:09 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/04 17:04:21 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			ft_check_room_coordinates_and_names(t_lem *g,
		t_input *i, t_rooms *r)
{
	t_rooms		*room_a;
	t_rooms		*room_b;

	room_a = r;
	while (room_a->next != NULL)
	{
		room_b = room_a->next;
		while (room_b->next != NULL)
		{
			if (ft_strequ(room_a->name, room_b->name))
				ft_print_input(g, i, 772);
			if (room_a->x == room_b->x && room_a->y == room_b->y)
				ft_print_input(g, i, 771);
			room_b = room_b->next;
		}
		room_a = room_a->next;
	}
}

static void		ft_room_or_link(t_lem *g, t_input *in)
{
	int			i;
	int			l;
	int			space;
	int			minus;

	l = (int)ft_strlen(g->input->data);
	space = 0;
	minus = 0;
	i = -1;
	while (++i < l)
	{
		if (!(ft_isprint(g->input->data[i])))
			ft_print_input(g, in, 66);
		if (g->input->data[i] == ' ')
			space++;
		if (g->input->data[i] == '-')
			minus++;
	}
	if (space != 2 && minus == 1)
		g->flag_link = 1;
	else if (space != 2)
		ft_print_input(g, in, 66);
}

void			ft_room_or_link_or_comment(t_lem *g, t_input *i)
{
	if (ft_strequ(g->input->data, "##start"))
		ft_start(g, i);
	else if (ft_strequ(g->input->data, "##end"))
		ft_end(g, i);
	else
	{
		if (g->input->data[0] == 'L' && !g->flag_link)
			ft_print_input(g, i, 4);
		if (g->input->data[0] != '#')
		{
			if (!g->flag_link)
			{
				ft_room_or_link(g, i);
				if (!g->flag_link)
				{
					ft_room(g, i);
					if (!g->flag_link)
						g->room = g->room->next;
				}
			}
		}
	}
}
