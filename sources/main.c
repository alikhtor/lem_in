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

#include <fcntl.h>
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
	else if (error_index == 55)
	{
		ft_putendl_fd("Room coordinates are not integers!", 2);
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
	g->input = g->input->next;
	return (0);
}

void		ft_add_room_type(t_lem *g, char *room_type)
{
	if (ft_strequ(room_type, "start"))
		g->room->type = ft_strdup("start");
	else if (ft_strequ(room_type, "end"))
		g->room->type = ft_strdup("end");
	else
		g->room->type = ft_strdup("room");
}

int 		ft_link(t_lem *g)
{

	return (0);
}

int         ft_room(t_lem *g)
{
	int     i;
	int     line_len;

	i = -1;
	line_len = (int)ft_strlen(g->input->data);
	while (++i < line_len)
	{
		if (g->input->data[i] == ' ')
		{
			g->room->name = ft_strnew((size_t)i);
			g->room->name = ft_memcpy(g->room->name, g->input->data, (size_t) i);
			if (!(ft_isdigit(g->input->data[i + 1])))
				return (ft_error(55));
			g->room->x = ft_atoi(g->input->data + i + 1);
			i++;
			while (ft_isdigit(g->input->data[i]))
				i++;
			if (!(ft_isdigit(g->input->data[i + 1])))
				return (ft_error(55));
			g->room->y = ft_atoi(g->input->data + i);
			break;
		}
	}
	ft_add_room_type(g, "");
	g->room->next = (t_rooms*)malloc(sizeof(t_rooms));
	return (2);
}

int 		ft_room_or_link(t_lem *g)
{
	int     i;
	int     line_len;
	int     space;

	i = -1;
	space = 0;
	line_len = (int)ft_strlen(g->input->data);
	while (++i < line_len)
	{
		if (!(ft_isprint(g->input->data[i])))
			return (1);
		if (g->input->data[i] == ' ')
			space++;
	}
	if (space == 2)
		return (ft_room(g));
	else if (space == 0)
		return (ft_link(g));
	else
		return (1);
}

int 		ft_start(t_lem *g)
{
	g->input = g->input->next;
	g->flag_start += 1;
	if (g->flag_start > 1)
		return (ft_error(22));
	if (g->input->next == NULL)
		return (ft_error(2));
	if (ft_room_or_link(g) == 1)
		return (ft_error(44));
	ft_strdel(&g->room->type);
	ft_add_room_type(g, "start");
	g->room = g->room->next;
	g->input = g->input->next;
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
	if (ft_room_or_link(g) == 1)
		return (ft_error(44));
	ft_strdel(&g->room->type);
	ft_add_room_type(g, "end");
	g->room = g->room->next;
	g->input = g->input->next;
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
	int     todo;

	if (ft_strequ(g->input->data, "##start"))
	{
		if (ft_start(g))
			return (1);
	}
	if (ft_strequ(g->input->data, "##end"))
	{
		if (ft_end(g))
			return (1);
	}
	if (g->input->data[0] != '#')
	{
		todo = ft_room_or_link(g);
		if (todo == 1)
			return (1);
		else if (todo == 2)
			g->room = g->room->next;
	}
	return (0);
}

int			ft_parse_and_check_input(t_lem *g)
{
	if (g->input->next == NULL || ft_check_ants(g))
		return (ft_error(1));
	while (g->input->next != NULL)
	{
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
	int 	fd;

	start = g->input;
	fd = open("/Users/alikhtor/Desktop/lem_in_github/test1", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		g->input->data = ft_strdup(line);
		g->input->next = (t_input *) malloc(sizeof(t_input));
		g->input = g->input->next;
		ft_strdel(&line);
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
}

void	ft_print_room_s(t_rooms *room)
{
	t_rooms *r;
	r = room;
	while (r->next != NULL)
	{
		ft_printf("room name :%s\n", r->name);
		ft_printf("room type :%s\n", r->type);
		r = r->next;
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
	ft_print_input(input_start);
	ft_print_room_s(rooms_start);
	//add a function where to delete all data and free lists
	return (0);
}
