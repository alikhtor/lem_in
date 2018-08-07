/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:26:47 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/04 16:56:49 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		ft_check_ants(t_lem *g, t_input *i)
{
	int			j;

	while (g->input->data[0] == '#')
	{
		if (ft_strequ(g->input->data, "##start") ||
				ft_strequ(g->input->data, "##end"))
			ft_print_input(g, i, 66);
		g->input = g->input->next;
	}
	j = 0;
	while (g->input->data[j])
	{
		if (!ft_isdigit(g->input->data[j]))
			ft_print_input(g, i, 11);
		j++;
	}
	g->ants = ft_atoi(g->input->data);
	if (g->ants <= 0)
		ft_print_input(g, i, 1);
	g->input = g->input->next;
}

static void		ft_check_input(t_lem *g, t_input *i)
{
	if (!(g->flag_start) && !(g->flag_end))
		ft_print_input(g, i, 992);
	else if (!(g->flag_start))
		ft_print_input(g, i, 2);
	else if (!(g->flag_end))
		ft_print_input(g, i, 3);
}

void			ft_parse_and_check_input(t_lem *g, t_input *i, t_rooms *r)
{
	if (g->input->next == NULL)
		ft_print_input(g, i, 66);
	ft_check_ants(g, i);
	if (g->input->next == NULL)
		ft_print_input(g, i, 44);
	while (g->input->next != NULL)
	{
		if (ft_strequ(g->input->data, "") && !g->flag_link)
			ft_print_input(g, i, 67);
		if (ft_strequ(g->input->data, "") && g->flag_link)
			break ;
		if (!g->flag_link)
			ft_room_or_link_or_comment(g, i);
		if (g->flag_link)
		{
			if (ft_check_link(g))
				break ;
		}
		if (!g->flag_link)
			ft_check_room_coordinates_and_names(g, i, r);
		else
			ft_check_input(g, i);
		g->input = g->input->next;
	}
	ft_check_input(g, i);
}

void			ft_write_input(t_lem *g)
{
	char		*line;
	t_input		*start;

	start = g->input;
	while (get_next_line(0, &line) > 0)
	{
		g->input->data = ft_strdup(line);
		g->input->next = (t_input*)malloc(sizeof(t_input));
		g->input->next->data = NULL;
		g->input = g->input->next;
		ft_strdel(&line);
	}
	g->input->next = NULL;
	g->input = start;
}
