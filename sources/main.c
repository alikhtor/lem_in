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

void	        ft_print_room_s(t_rooms *room)
{
    t_rooms     *r;
    r = room;
    while (r->next != NULL)
    {
        ft_printf("room name :%s\nroom type :%s\nroom coords: x=%d, y=%d\n", r->name, r->type, r->x, r->y);
        r = r->next;
    }
}

void	        ft_print_link_s(t_links *link)
{
    t_links     *l;
    l = link;
    while (l->next != NULL)
    {
        ft_printf("links :%s-%s\n", l->l1, l->l2);
        l = l->next;
    }
}

void		    ft_allocate_memmory(t_lem *g)
{
	ft_bzero(g, sizeof(t_lem));
	g->input = (t_input*)malloc(sizeof(t_input));
	g->room = (t_rooms*)malloc(sizeof(t_rooms));
	g->link = (t_links*)malloc(sizeof(t_links));
	ft_bzero(g->input, sizeof(t_input));
	ft_bzero(g->room, sizeof(t_rooms));
	ft_bzero(g->link, sizeof(t_links));
}

void        ft_save_kid_name(t_rooms *r, char *name)
{
    r->kid->kid_name = ft_strdup(name);
    r->kid->next = (t_kid_rooms*)malloc(sizeof(t_kid_rooms));
    ft_bzero(r->kid->next, sizeof(t_kid_rooms));
    r->kid = r->kid->next;

}

void            ft_allocate_memory_for_kids(t_rooms *r)
{
    while (r->next != NULL)
    {
        r->kid = (t_kid_rooms*)malloc(sizeof(t_kid_rooms));
        ft_bzero(r->kid, sizeof(t_kid_rooms));
        r = r->next;
    }
}

void    ft_k(t_lem *g, t_rooms *r_kid)
{
    t_links *l;
    t_kid_rooms *k;

    k = r_kid->kid;
    l = g->link;
    while (l->next != NULL)
    {
        if (ft_strequ(r_kid->name, l->l1) && !(ft_strequ(r_kid->parent, l->l2)))
            ft_save_kid_name(r_kid, l->l2);
        else if (ft_strequ(r_kid->name, l->l2) && !(ft_strequ(r_kid->parent, l->l1)))
            ft_save_kid_name(r_kid, l->l1);
        l = l->next;
    }
    r_kid->kid = k;
}

int    ft_s(t_rooms *r, t_lem *g, int seen)
{
    t_rooms *r_kid;
    t_kid_rooms *tmp;

    while (r->kid->next)
    {
        r_kid = g->room;
        tmp = r->kid->next;
        while (r_kid->next)
        {
            if (ft_strequ(r->kid->kid_name, r_kid->name))
            {
                r_kid->seen = seen + 1;
                if (!r_kid->parent)
                    r_kid->parent = ft_strdup(r->name);
                if (ft_strequ(r_kid->type, "end"))
                    return (1);
                ft_k(g, r_kid);
            }
            r_kid = r_kid->next;
        }
        ft_strdel(&(r->kid->kid_name));
        ft_memdel((void **)&r->kid);
        r->kid = tmp;
    }
    return (0);
}

int    ft_parents_and_kids(t_lem *g)
{
    t_rooms *r;
    int     seen;

    r = g->room;
    seen = 1;
    while (r->next != NULL)
    {
        if (r->seen == seen)
        {
            if (ft_s(r, g, seen))
                return (0);
            seen++;
            r = g->room;
        }
        else
            r = r->next;
    }
    return (1);
}

void    ft_start_kids(t_rooms *r_start, t_links *l_start)
{
    t_rooms *r;
    t_links *l;
    t_kid_rooms *k;

    r = r_start;
    ft_allocate_memory_for_kids(r);
    while (r->next->next != NULL)
    {
        if (ft_strequ(r->type, "start"))
        {
            r->seen = 1;
            k = r->kid;
            l = l_start;
            while (l->next->next != NULL)
            {
                if (ft_strequ(r->name, l->l1))
                    ft_save_kid_name(r, l->l2);
                else if (ft_strequ(r->name, l->l2))
                    ft_save_kid_name(r, l->l1);
                l = l->next;
            }
            r->kid = k;
            break;
        }
        r = r->next;
    }
}

void            ft_delete_rooms(t_lem *g)
{
    t_rooms     *r;
    t_rooms     *temp_r;
    t_kid_rooms *k;
    t_kid_rooms *temp_k;

    while (g->room)
    {
        temp_r = g->room->next;
//          if (r->type != NULL)
            ft_strdel(&g->room->type);
//        if (r->parent != NULL)
            ft_strdel(&g->room->parent);
//        if (r->name != NULL)
            ft_strdel(&g->room->name);
        while (g->room->kid)
        {
            temp_k = g->room->kid->next;
//  if (k->kid_name != NULL)
            ft_strdel(&g->room->kid->kid_name);
            ft_memdel((void **)&g->room->kid);
            g->room->kid = temp_k;
        }
        ft_memdel((void **)&g->room);
        g->room = temp_r;
//        free(k);
//        temp_r->kid = NULL;
//        ft_bzero(temp_r, sizeof(t_rooms));
//        free(temp_r);
//        r = NULL;

    }
}

void            ft_delete_all_structs(t_lem *g)
{
//    t_input *i;
    t_input *temp_i;
    t_links *temp_l;

//    i = g->input;
    while (g->input)
    {
//        if (i->data != NULL)
        temp_i = g->input->next;
            ft_strdel(&g->input->data);
//        i = i->next;
        ft_memdel((void **)&g->input);
        g->input = temp_i;
    }
//    free(g->input);
    while (g->link)
    {
        temp_l = g->link->next;
//        if (l->l1 != NULL)
            ft_strdel(&g->link->l1);
//        if (l->l2 != NULL)
            ft_strdel(&g->link->l2);
        ft_memdel((void **)&g->link);
        g->link = temp_l;
    }
    ft_delete_rooms(g);

//    free(g->input);
//    free(g->room);
//    free(g->link);
    ft_memdel((void **)&g);
}

static int      ft_general_check(t_lem *g, t_rooms *r, t_links *l, t_input *i)
{
    if (ft_parse_and_check_input(g))
    {
        g->room = r;
        g->link = l;
        g->input = i;
        return (1);
    }
    g->room = r;
    g->link = l;
    g->input = i;
    if (ft_check_room_coordinates_and_names(r))
        return (1);
    ft_start_kids(r,l);
    if (ft_parents_and_kids(g))
        return (ft_error(880));
    return (0);
}

int			    main(void)
{
	t_lem	    *general;
	t_rooms	    *rooms_start;
	t_links     *links_start;
	t_input	    *input_start;

	general = (t_lem*)malloc(sizeof(t_lem));
	ft_allocate_memmory(general);
	rooms_start = general->room;
	links_start = general->link;
	input_start = general->input;
	ft_write_input(general);
    if (ft_general_check(general, rooms_start, links_start, input_start)) {
        ft_printf("---NE OK---\n");
        system ("leaks -quiet lem-in");
        return (1);
    }
    ft_print_input(input_start);
    ft_print_room_s(rooms_start);
    ft_print_link_s(links_start);


//    ft_delete_all_structs(general);

	//add a function where to delete all data and free lists
    ft_printf("---OK---\n");
    system ("leaks -quiet lem-in");
	return (0);
}
