/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:17:49 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/04 17:07:47 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		ft_save_kid_name(t_rooms *r, char *name)
{
	r->kid->kid_name = ft_strdup(name);
	r->kid->next = (t_kid_rooms*)malloc(sizeof(t_kid_rooms));
	ft_bzero(r->kid->next, sizeof(t_kid_rooms));
	r->kid = r->kid->next;
}

static void		ft_allocate_memory_for_kids(t_rooms *r)
{
	while (r->next != NULL)
	{
		r->kid = (t_kid_rooms*)malloc(sizeof(t_kid_rooms));
		ft_bzero(r->kid, sizeof(t_kid_rooms));
		r = r->next;
	}
}

static int		ft_check_l_for_non_doubles(t_lem *g,
		t_kid_rooms *s_r, char *link_name)
{
	t_rooms		*r;
	t_kid_rooms	*k;

	r = g->room;
	k = s_r;
	while (r)
	{
		while (k)
		{
			if (ft_strequ(k->kid_name, link_name))
				return (1);
			k = k->next;
		}
		r = r->next;
	}
	return (0);
}

static void		ft_compare_names(t_lem *g, t_rooms *r, t_links *l_start)
{
	t_kid_rooms	*k;
	t_links		*l;

	k = r->kid;
	l = l_start;
	while (l->next)
	{
		if (!l->used && ft_strequ(r->name, l->l1) &&
				!ft_check_l_for_non_doubles(g, k, l->l2))
		{
			ft_save_kid_name(r, l->l2);
			l->used = 1;
		}
		else if (!l->used && ft_strequ(r->name, l->l2) &&
				!ft_check_l_for_non_doubles(g, k, l->l1))
		{
			ft_save_kid_name(r, l->l1);
			l->used = 1;
		}
		l = l->next;
	}
	r->kid = k;
}

void			ft_start_kids(t_lem *g, t_rooms *r_start, t_links *l_start)
{
	t_rooms		*r;

	r = r_start;
	ft_allocate_memory_for_kids(r);
	while (r->next)
	{
		if (ft_strequ(r->type, "start"))
		{
			r->seen = 1;
			ft_compare_names(g, r, l_start);
			break ;
		}
		r = r->next;
	}
}
