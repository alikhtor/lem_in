/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:14:51 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/04 17:01:07 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			ft_add_room_type(t_lem *g, char *room_type)
{
	if (ft_strequ(room_type, "start"))
		g->room->type = ft_strdup("start");
	else if (ft_strequ(room_type, "end"))
		g->room->type = ft_strdup("end");
	else
		g->room->type = ft_strdup("room");
}

static void		ft_check_for_negative_integer(t_lem *g, t_input *in, int i)
{
	if (g->input->data[i + 1] == '-')
	{
		if (!(ft_isdigit(g->input->data[i + 2])))
			ft_print_input(g, in, 55);
	}
	else if (!(ft_isdigit(g->input->data[i + 1])))
		ft_print_input(g, in, 55);
}

static void		ft_check_integer_coordinate(t_lem *g, t_input *in, int *i)
{
	while (g->input->data[*i])
	{
		if (g->input->data[*i] == ' ' || g->input->data == '\0')
			break ;
		if (!(ft_isdigit(g->input->data[*i])))
			ft_print_input(g, in, 773);
		*i = *i + 1;
	}
}

static void		ft_write_room_data(t_lem *g, t_input *in, int i)
{
	g->room->name = ft_strnew((size_t)i);
	g->room->name = ft_memcpy(g->room->name, g->input->data, (size_t)i);
	ft_check_for_negative_integer(g, in, i);
	g->room->x = ft_atoi(g->input->data + i + 1);
	if (g->input->data[i + 1] == '-')
		i++;
	i++;
	ft_check_integer_coordinate(g, in, &i);
	ft_check_for_negative_integer(g, in, i);
	g->room->y = ft_atoi(g->input->data + i);
	if (g->input->data[i + 1] == '-')
		i++;
	i++;
	ft_check_integer_coordinate(g, in, &i);
}

void			ft_room(t_lem *g, t_input *in)
{
	int			i;
	int			line_len;

	i = -1;
	line_len = (int)ft_strlen(g->input->data);
	while (++i < line_len)
	{
		if (g->input->data[i] == ' ')
		{
			ft_write_room_data(g, in, i);
			break ;
		}
	}
	ft_add_room_type(g, "");
	g->room->next = (t_rooms*)malloc(sizeof(t_rooms));
	ft_bzero(g->room->next, sizeof(t_rooms));
}
