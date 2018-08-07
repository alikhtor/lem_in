/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 15:16:46 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/04 17:53:57 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void			ft_allocate_memory(t_lem *g)
{
	ft_bzero(g, sizeof(t_lem));
	g->input = (t_input*)malloc(sizeof(t_input));
	g->room = (t_rooms*)malloc(sizeof(t_rooms));
	g->link = (t_links*)malloc(sizeof(t_links));
	g->way = (t_way*)malloc(sizeof(t_way));
	g->ant = (t_ant*)malloc(sizeof(t_ant));
	ft_bzero(g->ant, sizeof(t_ant));
	ft_bzero(g->way, sizeof(t_way));
	ft_bzero(g->input, sizeof(t_input));
	ft_bzero(g->room, sizeof(t_rooms));
	ft_bzero(g->link, sizeof(t_links));
}

void				ft_print_input(t_lem *g, t_input *print, int index)
{
	if (index == 0)
	{
		while (print->next)
		{
			ft_printf("%s\n", print->data);
			if (ft_strequ(print->data, g->input->data))
				break ;
			print = print->next;
		}
		ft_printf("\n");
		return ;
	}
	while (print->next)
	{
		ft_printf("%s\n", print->data);
		if (ft_strequ(print->data, g->input->data))
			exit(ft_error(index));
		print = print->next;
	}
	if (g->input->next == NULL)
		exit(ft_error(index));
}

static void			ft_find_identical_links(t_lem *g)
{
	t_links			*la;
	t_links			*lb;

	la = g->link;
	while (g->link)
	{
		lb = g->link->next;
		while (lb)
		{
			if ((ft_strequ(g->link->l1, lb->l1) &&
						ft_strequ(g->link->l2, lb->l2)) ||
					(ft_strequ(g->link->l2, lb->l1) &&
					ft_strequ(g->link->l1, lb->l2)))
				g->link->used = 1;
			lb = lb->next;
		}
		g->link = g->link->next;
	}
	g->link = la;
}

static void			ft_general_check(t_lem *g, t_rooms *r,
		t_links *l, t_input *i)
{
	t_input			*input_to_print;

	ft_parse_and_check_input(g, i, r);
	if (!g->flag_link)
		ft_print_input(g, i, 991);
	input_to_print = g->input;
	g->input = i;
	g->room = r;
	g->link = l;
	ft_find_identical_links(g);
	ft_start_kids(g, r, l);
	if (!ft_p_and_k(g))
	{
		g->input = input_to_print;
		ft_print_input(g, i, 880);
	}
	g->input = input_to_print;
	ft_print_input(g, i, 0);
}

int					main(void)
{
	t_lem			*general;
	t_rooms			*rooms_start;
	t_links			*links_start;
	t_input			*input_start;
	t_ant			*ant_start;

	general = (t_lem*)malloc(sizeof(t_lem));
	ft_allocate_memory(general);
	rooms_start = general->room;
	links_start = general->link;
	input_start = general->input;
	ant_start = general->ant;
	ft_write_input(general);
	ft_general_check(general, rooms_start, links_start, input_start);
	ft_move_ants(ft_find_the_way(rooms_start), general);
	general->input = input_start;
	general->ant = ant_start;
	return (0);
}
