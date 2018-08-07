/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 14:39:10 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/04 17:11:51 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		ft_allocate_memory_for_next_room(t_lem *g)
{
	g->room->next = (t_rooms*)malloc(sizeof(t_rooms));
	ft_bzero(g->room->next, sizeof(t_rooms));
}

static void		ft_check_start_or_end(t_lem *g, t_input *in)
{
	int			i;
	int			line_len;

	i = -1;
	line_len = (int)ft_strlen(g->input->data);
	while (++i < line_len)
	{
		if (g->input->data[i] == ' ')
		{
			g->room->name = ft_strnew((size_t)i);
			g->room->name = ft_memcpy(g->room->name, g->input->data, (size_t)i);
			if (!(ft_isdigit(g->input->data[i + 1])))
				ft_print_input(g, in, 55);
			g->room->x = ft_atoi(g->input->data + i + 1);
			i++;
			while (ft_isdigit(g->input->data[i]))
				i++;
			if (!(ft_isdigit(g->input->data[i + 1])))
				ft_print_input(g, in, 55);
			g->room->y = ft_atoi(g->input->data + i);
			break ;
		}
	}
	ft_add_room_type(g, "");
	ft_allocate_memory_for_next_room(g);
}

static void		ft_start_or_end(t_lem *g, t_input *in)
{
	int			l;
	int			i;
	int			space;

	l = (int)ft_strlen(g->input->data);
	space = 0;
	i = -1;
	while (++i < l)
	{
		if (!(ft_isprint(g->input->data[i])))
			ft_print_input(g, in, 551);
		if (g->input->data[i] == ' ')
			space++;
	}
	if (space != 2)
		ft_print_input(g, in, 551);
	ft_check_start_or_end(g, in);
}

void			ft_start(t_lem *g, t_input *i)
{
	g->input = g->input->next;
	if (g->input->next == NULL)
		ft_print_input(g, i, 2);
	g->flag_start += 1;
	if (g->flag_start > 1)
		ft_print_input(g, i, 22);
	if (g->input->data[0] == 'L' || g->input->data[0] == '#')
		ft_print_input(g, i, 4);
	ft_start_or_end(g, i);
	ft_strdel(&g->room->type);
	ft_add_room_type(g, "start");
	g->room = g->room->next;
}

void			ft_end(t_lem *g, t_input *i)
{
	g->input = g->input->next;
	if (g->input->next == NULL)
		ft_print_input(g, i, 3);
	g->flag_end += 1;
	if (g->flag_end > 1)
		ft_print_input(g, i, 33);
	if (g->input->data[0] == 'L' || g->input->data[0] == '#')
		ft_print_input(g, i, 4);
	ft_start_or_end(g, i);
	ft_strdel(&g->room->type);
	ft_add_room_type(g, "end");
	g->room = g->room->next;
}
