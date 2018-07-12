/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 15:16:46 by alikhtor          #+#    #+#             */
/*   Updated: 2018/07/10 17:14:14 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		ft_error_2(int error_index, int *error)
{
	if (error_index == 22)
	{
		ft_putendl_fd("Error! More than one start room is found!", 2);
		*error = 1;
	}
	else if (error_index == 33)
	{
		ft_putendl_fd("Error! More than one end room is found!", 2);
		*error = 1;
	}
	else if (error_index == 44)
	{
		ft_putendl_fd("Error! Wrong room or link!", 2);
		*error = 1;
	}
}

int			ft_error(int error_index)
{
	int		error;

	error = 0;
	if (error_index == 1)
	{
		ft_putendl_fd("Error! Wrong amount of ants!", 2);
		error = 1;
	}
	else if (error_index == 2)
	{
		ft_putendl_fd("Error! Start room is not found!", 2);
		error = 1;
	}
	else if (error_index == 3)
	{
		ft_putendl_fd("Error! End room is not found!", 2);
		error = 1;
	}
	else
		ft_error_2(error_index, &error);
	return (error);
}

int			ft_check_ants(t_lem *g)
{
	int 	temp_ants;

	while (g->input->data[0] == '#')
	{
		if (g->input->data[1] == '#' || g->input->next->next == NULL)
			return (1);
		g->input = g->input->next;
	}
	temp_ants = ft_atoi(g->input->data);
	if (temp_ants <= 0)
		return (1);
	g->ants = temp_ants;
	// ft_printf("ants num: %d\n", g->ants);
	return (0);
}

void		ft_add_room_type(t_lem *g, char *room_type)
{
	if (ft_strequ(room_type, "start"))
		g->room->type = "start";
	else if (ft_strequ(room_type, "end"))
		g->room->type = "end";
	else
		g->room->type = "room";
}

void		ft_link(t_lem *g)
{
	return ;
}

void		ft_room(t_lem *g)
{
	int i;

	i = 0;
	int space = 0;
	while (i < ft_strlen(g->input->data))
	{
		if (g->input->data[i] == ' ')
			space++;
		if (space == 1)
		{
			g->room->name = ft_memcpy(g->room->name, g->input, i);
			//i++;
			g->room->x = ft_atoi(g->input->data + i + 1);
		}
		else if (space == 2)
			g->room->y = ft_atoi(g->input->data + i + 1);
		i++;
	}
	ft_add_room_type(g, "");
	g->room->next = (t_rooms*)malloc(sizeof(t_rooms));
	g->room = g->room->next;
	return ;
}

int 		ft_room_or_link(t_lem *g)
{
	int 	i;
	int 	space;

	i = 0;
	space = 0;
	while (i < ft_strlen(g->input->data) && ft_isprint(g->input->data[i]))
	{
		if (g->input->data[i] == ' ')
			space++;
		i++;
	}
	if (space == 2)
		ft_room(g);
	else if (space == 0)
		ft_link(g);
	else
		return (1);
	return (0);
}

int 		ft_start(t_lem *g)
{
   	g->input = g->input->next;
	g->flag_start += 1;
	if (g->flag_start > 1)
		return (ft_error(22));
	if (g->input->next == NULL)
		return (ft_error(2));
	if (ft_room_or_link(g))
		return (ft_error(44));
	ft_add_room_type(g, "start");
	//write data into rooms struct! and switch to the next list!
	// ft_printf("start coords are: %s\n", g->input->data);
	return (0);
}

int 		ft_end(t_lem *g)
{
	g->input = g->input->next;
	g->flag_end += 1;
	if (g->flag_end > 1)
		return (ft_error(33));
	if (g->input->next == NULL)
		return (ft_error(3));
	if (ft_room_or_link(g))
		return (ft_error(44));
	ft_add_room_type(g, "end");
	// ft_printf("end coords are: %s\n", end->data);
	return (0);
}

int			ft_check_input(t_lem *g)
{
	if (!(g->flag_start))
		return (ft_error(2));
	else if (!(g->flag_end))
		return (ft_error(3));
	return (0);
}

int 		ft_room_or_link_or_comment(t_lem *g)
{
	if (ft_strequ(g->input->data, "##start"))
	{
		if (ft_start(g))
			return (1);
	}
	else if (ft_strequ(g->input->data, "##end"))
	{
		if (ft_end(g))
			return (1);
	}
	else
	{
		if (g->input->data[0] != '#')
		{
			if (ft_room_or_link(g))
				return (1);
		}
	}
	return (0);
}

int			ft_parse_and_check_input(t_lem *g)
{
	if (g->input->next == NULL || ft_check_ants(g))
		return (ft_error(1));
	while (g->input->next != NULL)
	{
		// ft_printf("lst-data: %s\n", lst->data);
		if (ft_room_or_link_or_comment(g))
			return (1);
		g->input = g->input->next;
	}
	g->room->next = NULL;
	g->link->next = NULL;
	if (ft_check_input(g))
		return (1);
	return (0);
}

void		ft_write_input(t_lem *g)
{
	char 	*line;
	t_input *start;

	start = g->input;
	while (get_next_line(0, &line) > 0)
	{
		g->input->data = ft_strdup(line);
		ft_strdel(&line);
		g->input->next = (t_input*)malloc(sizeof(t_input));
		g->input = g->input->next;
	}
	g->input->next = NULL;
	g->input = start;
}

void		ft_print_input(t_input *print)
{
	while (print->next != NULL)
	{
		ft_printf("%s\n", print->data);
		print = print->next;
	}
}

void		ft_allocate_memmory(t_lem *g)
{
	ft_bzero(g, sizeof(t_lem));
	g->input = (t_input*)malloc(sizeof(t_input));
	g->room = (t_rooms*)malloc(sizeof(t_rooms));
	g->link = (t_links*)malloc(sizeof(t_links));
	ft_bzero(g->input, sizeof(t_input));
	ft_bzero(g->room, sizeof(t_rooms));
	ft_bzero(g->link, sizeof(t_links));
	return ;
}

void	ft_print_room_s(t_rooms *room)
{
	t_rooms *r;
	r = room;
	while (r->next != NULL)
	{
		ft_printf("room name :%s\n", r->name);
		ft_printf("room type :%s\n", r->type);
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
	//ft_print_input(input_start);
	ft_print_room_s(rooms_start);
	//add a function where to delete all data and free lists
	return (0);
}
