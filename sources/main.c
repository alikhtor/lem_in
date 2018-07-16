/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 15:16:46 by alikhtor          #+#    #+#             */
/*   Updated: 2018/07/13 10:25:40 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		ft_allocate_memmory(t_lem *g)
{
	ft_bzero(g, sizeof(t_lem));
	g->input = (t_input*)malloc(sizeof(t_input));
	g->room = (t_rooms*)malloc(sizeof(t_rooms));
	g->link = (t_links*)malloc(sizeof(t_links));
	ft_bzero(g->input, sizeof(t_input));
	ft_bzero(g->room, sizeof(t_rooms));
	ft_bzero(g->link, sizeof(t_links));
}

void	ft_print_room_s(t_rooms *room)
{
	t_rooms *r;
	r = room;
	while (r->next != NULL)
	{
		ft_printf("room name :%s\nroom type :%s\n", r->name, r->type);
		r = r->next;
	}
}

void	ft_print_link_s(t_links *link)
{
    t_links *l;
    l = link;
    while (l->next != NULL)
    {
        ft_printf("links :%s-%s\n", l->current, l->following);
        l = l->next;
    }
}

int			main(void)
{
	t_lem	*general;
	t_rooms	*rooms_start;
	t_links *links_start;
	t_input	*input_start;

	general = (t_lem*)malloc(sizeof(t_lem));
	ft_allocate_memmory(general);
	rooms_start = general->room;
	links_start = general->link;
	input_start = general->input;
	ft_write_input(general);
	if (ft_parse_and_check_input(general))
	{
		//add a function where to delete all data and free lists
		return (1);
	}
    ft_check_rooms_and_links(rooms_start, links_start);
	ft_print_input(input_start);
	ft_print_room_s(rooms_start);
    ft_print_link_s(links_start);
	//add a function where to delete all data and free lists
	return (0);
}
