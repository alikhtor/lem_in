/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 15:16:55 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/04 17:31:11 by alikhtor         ###   ########.fr       */
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

static int		ft_check_l_for_non_doubles(t_lem *g, char *link_name)
{
	t_rooms		*r;
	t_kid_rooms	*k;

	r = g->room;
	while (g->room)
	{
		k = g->room->kid;
		while (g->room->kid)
		{
			if (ft_strequ(r->kid->kid_name, link_name))
			{
				g->room->kid = k;
				g->room = r;
				return (1);
			}
			g->room->kid = g->room->kid->next;
		}
		g->room->kid = k;
		g->room = g->room->next;
	}
	g->room = r;
	return (0);
}

static void		ft_k(t_lem *g, t_rooms *r_kid, int seen)
{
	t_links		*l;
	t_kid_rooms	*k;

	r_kid->seen = seen + 1;
	k = r_kid->kid;
	l = g->link;
	while (l->next)
	{
		if (!l->used && ft_strequ(r_kid->name, l->l1) &&
				!(ft_strequ(r_kid->parent, l->l2)) &&
				!(ft_check_l_for_non_doubles(g, l->l2)))
		{
			ft_save_kid_name(r_kid, l->l2);
			l->used = 1;
		}
		else if (!l->used && ft_strequ(r_kid->name, l->l2) &&
				!(ft_strequ(r_kid->parent, l->l1)) &&
				!(ft_check_l_for_non_doubles(g, l->l1)))
		{
			ft_save_kid_name(r_kid, l->l1);
			l->used = 1;
		}
		l = l->next;
	}
	r_kid->kid = k;
}

static int		ft_p(t_rooms *r, t_lem *g, int seen)
{
	t_rooms		*r_kid;
	t_kid_rooms	*tmp_r;

	tmp_r = r->kid;
	while (r->kid->next)
	{
		r_kid = g->room;
		while (r_kid)
		{
			if (ft_strequ(r->kid->kid_name, r_kid->name))
			{
				r_kid->parent = ft_strdup(r->name);
				if (ft_strequ(r_kid->type, "end"))
				{
					r->kid = tmp_r;
					return (1);
				}
				ft_k(g, r_kid, seen);
			}
			r_kid = r_kid->next;
		}
		r->kid = r->kid->next;
	}
	r->kid = tmp_r;
	return (0);
}

int				ft_p_and_k(t_lem *g)
{
	t_rooms		*r;
	int			seen;

	r = g->room;
	seen = 1;
	while (r->next != NULL)
	{
		if (r->seen == seen && r->kid->next != NULL)
		{
			if (ft_p(r, g, seen))
				return (1);
			seen++;
			r = g->room;
		}
		else
			r = r->next;
	}
	return (0);
}
