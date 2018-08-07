/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 14:00:58 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/04 17:27:57 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			ft_make_way_lst(char **the_way, t_lem *g)
{
	t_way		*way_tmp;
	int			size;
	int			i;

	size = -1;
	i = -1;
	while (the_way[++i] != NULL)
		size++;
	way_tmp = g->way;
	while (size != -1)
	{
		if (size == 0)
			g->way->end = 1;
		g->way->name = ft_strdup(the_way[size]);
		if (size > 0)
		{
			g->way->next = (t_way *)malloc(sizeof(t_way));
			ft_bzero(g->way->next, sizeof(t_way));
			g->way = g->way->next;
		}
		size--;
	}
	g->way = way_tmp;
	ft_free_way_str(the_way);
}

void			ft_make_ant_lst(t_lem *g)
{
	t_ant		*ant_tmp;
	int			i;

	ant_tmp = g->ant;
	i = 1;
	while (i <= g->ants)
	{
		g->ant->ant_num = i;
		g->ant->room = g->way;
		if (i < g->ants)
		{
			g->ant->next = (t_ant*)malloc(sizeof(t_ant));
			ft_bzero(g->ant->next, sizeof(t_ant));
			g->ant = g->ant->next;
		}
		i++;
	}
	g->ant = ant_tmp;
}

int				ft_one_ant_can_move(t_lem *g)
{
	if (g->ant->room->next && !g->ant->room->next->used)
	{
		g->ant->room->used = 0;
		g->ant->room = g->ant->room->next;
		if (g->ant->room->end != 1)
			g->ant->room->used = 1;
		return (1);
	}
	if (g->ant->room->next->used)
		return (0);
	return (0);
}

int				ft_ants_can_move(t_lem *g)
{
	t_ant		*init_ant;

	if (!g->ant)
		return (0);
	if (g->ant->room->end)
		g->ant = g->ant->next;
	init_ant = g->ant;
	while (g->ant && ft_one_ant_can_move(g))
	{
		ft_printf("L%d-%s ", g->ant->ant_num, g->ant->room->name);
		g->ant = g->ant->next;
	}
	if (!g->ant || !ft_one_ant_can_move(g))
	{
		g->ant = init_ant;
		return (1);
	}
	g->ant = init_ant;
	return (0);
}

void			ft_move_ants(char **the_way, t_lem *g)
{
	ft_make_way_lst(the_way, g);
	ft_make_ant_lst(g);
	while (g->ants)
	{
		while (ft_ants_can_move(g))
			ft_printf("\n");
		g->ants--;
	}
}
