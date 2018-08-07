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

void			ft_free_way_str(char **the_way)
{
	int			i;

	i = 0;
	while (the_way[i] != NULL)
	{
		free(the_way[i]);
		i++;
	}
	free(the_way);
}

static int		ft_path_length(t_rooms *r_start)
{
	char		*name;
	int			size;
	t_rooms		*r;

	size = 1;
	r = r_start;
	while (r)
	{
		if (ft_strequ(r->type, "end"))
		{
			name = r->parent;
			r = r_start;
		}
		else if (ft_strequ(r->name, name))
		{
			size++;
			if (ft_strequ(r->type, "start"))
				break ;
			name = r->parent;
			r = r_start;
		}
		else
			r = r->next;
	}
	return (size);
}

static void		ft_conditions(t_rooms *r_start, int i,\
		char *name, char **the_way)
{
	t_rooms		*r;

	r = r_start;
	while (r)
	{
		if (ft_strequ(r->type, "end"))
		{
			the_way[i] = ft_strdup(r->name);
			i = i + 1;
			name = r->parent;
			r = r_start;
		}
		else if (ft_strequ(r->name, name))
		{
			the_way[i] = ft_strdup(r->name);
			i = i + 1;
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

char			**ft_find_the_way(t_rooms *r_start)
{
	char		**the_way;
	int			i;
	char		*name;

	i = ft_path_length(r_start);
	the_way = (char**)malloc(sizeof(char*) * (i + 1));
	i = 0;
	name = NULL;
	ft_conditions(r_start, i, name, the_way);
	return (the_way);
}
