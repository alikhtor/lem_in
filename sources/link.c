/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:20:18 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/04 16:20:54 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			ft_find_identical_links(t_lem *g)
{
	t_links		*la;
	t_links		*lb;

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

static int		ft_check_link_2(char **tmp_l1, char **tmp_l2)
{
	if (ft_strequ(*tmp_l1, "") || ft_strequ(*tmp_l2, ""))
	{
		ft_strdel(tmp_l1);
		ft_strdel(tmp_l2);
		return (ft_error(66));
	}
	if (ft_strequ(*tmp_l1, *tmp_l2))
	{
		ft_strdel(tmp_l1);
		ft_strdel(tmp_l2);
		return (ft_error(66));
	}
	if (*tmp_l1[0] == 'L' || *tmp_l2[0] == 'L')
	{
		ft_strdel(tmp_l1);
		ft_strdel(tmp_l2);
		return (ft_error(66));
	}
	return (0);
}

static int		ft_work_with_link(t_lem *g, int flag_minus, size_t l, size_t ml)
{
	char		*tmp_l1;
	char		*tmp_l2;

	if (flag_minus != 1)
		return (ft_error(66));
	tmp_l1 = ft_strnew(ml);
	tmp_l1 = ft_memcpy(tmp_l1, g->input->data, ml);
	tmp_l2 = ft_strnew((size_t)l - ml);
	tmp_l2 = ft_memcpy(tmp_l2, g->input->data + (ml + 1), (size_t)l - (ml + 1));
	if (ft_check_link_2(&tmp_l1, &tmp_l2))
		return (1);
	g->link->l1 = ft_strdup(tmp_l1);
	g->link->l2 = ft_strdup(tmp_l2);
	ft_strdel(&tmp_l1);
	ft_strdel(&tmp_l2);
	g->link->next = (t_links*)malloc(sizeof(t_links));
	ft_bzero(g->link->next, sizeof(t_links));
	g->link = g->link->next;
	return (0);
}

int				ft_link(t_lem *g)
{
	int			flag_minus;
	size_t		len;
	size_t		medium_len;

	flag_minus = 0;
	len = 0;
	medium_len = 0;
	while (g->input->data[len] != '\0')
	{
		if (!(ft_isprint(g->input->data[len])))
			return (ft_error(66));
		if (g->input->data[len] == '-')
		{
			medium_len = (size_t)len;
			flag_minus++;
		}
		len++;
	}
	return (ft_work_with_link(g, flag_minus, len, medium_len));
}

int				ft_check_link(t_lem *g)
{
	if (g->input->data[0] != '#')
	{
		if (ft_link(g))
		{
			return (1);
		}
	}
	return (0);
}
