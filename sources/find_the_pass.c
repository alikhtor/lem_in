/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_the_pass.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 16:04:56 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/04 16:32:21 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static void		ft_path_length_2(t_rooms *r, t_rooms *r_start,
	char **name, int *size)
{
	int			end_flag;

	end_flag = 0;
	while (r)
	{
		if (!end_flag && ft_strequ(r->type, "end"))
		{
			end_flag = 1;
			*name = r->parent;
			r = r_start;
		}
		else if (ft_strequ(r->name, *name))
		{
			*size = *size + 1;
			if (ft_strequ(r->type, "start"))
				break ;
			*name = r->parent;
			r = r_start;
		}
		else
			r = r->next;
	}
}

static int		ft_path_length(t_rooms *r_start)
{
	char		*name;
	int			size;
	t_rooms		*r;

	size = 1;
	r = r_start;
	name = NULL;
	ft_path_length_2(r, r_start, &name, &size);
	return (size);
}

static void		ft_conditions_2(t_rooms *r, t_rooms *r_start,
	char **the_way, char *name)
{
	int			i;

	i = 0;
	while (r)
	{
		if (i == 0 && ft_strequ(r->type, "end"))
		{
			the_way[i] = ft_strdup(r->name);
			i++;
			name = r->parent;
			r = r_start;
		}
		else if (ft_strequ(r->name, name))
		{
			the_way[i] = ft_strdup(r->name);
			i++;
			if (ft_strequ(r->type, "start"))
				break ;
			name = r->parent;
			r = r_start;
		}
		else
			r = r->next;
	}
	the_way[i] = NULL;
}

static void		ft_conditions(t_rooms *r_start, char **the_way)
{
	t_rooms		*r;
	char		*name;

	name = NULL;
	r = r_start;
	ft_conditions_2(r, r_start, the_way, name);
}

char			**ft_find_the_way(t_rooms *r_start)
{
	char		**the_way;
	int			room_amount;

	room_amount = ft_path_length(r_start);
	the_way = (char**)malloc(sizeof(char*) * (room_amount + 1));
	ft_conditions(r_start, the_way);
	return (the_way);
}
