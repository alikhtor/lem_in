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
		ft_putendl_fd("Error! Start was not found!", 2);
		error = 1;
	}
	else if (error_index == 3)
	{
		ft_putendl_fd("Error! End was not found!", 2);
		error = 1;
	}
	return (error);
}

int			ft_check_ants(t_lem *g, char *ants_from_lst)
{
	int 	temp_ants;

	temp_ants = ft_atoi(ants_from_lst);
	if (temp_ants <= 0)
		return (1);
	g->ants = temp_ants;
	ft_printf("ants num: %d\n", g->ants);
	return (0);
}

void		ft_start(t_lem *g, t_input *start)
{
	g->flag_start = 1;
   	start = start->next;
	//write data into rooms struct! and switch to the next list!
	ft_printf("start coords are: %s\n", start->data);
}

void		ft_end(t_lem *g, t_input *end)
{
	g->flag_end = 1;
	end = end->next;
	ft_printf("end coords are: %s\n", end->data);
}

int			ft_parse_input(t_lem *g)
{
	t_input	*lst;

	lst = g->input;
	if (lst->next == NULL || ft_check_ants(g, lst->data))
		return (ft_error(1));
	while (lst->next != NULL)
	{
		if (!(g->flag_start) && ft_strequ(lst->data, "##start"))
		{
			if (lst->next->next == NULL)
				return (ft_error(2));
			ft_start(g, lst);
		}
		if (!(g->flag_end) && ft_strequ(lst->data, "##end"))
		{
			if (lst->next->next == NULL)
				return (ft_error(3));
			ft_end(g, lst);
		}
		//ft_room_or_link(g, lst);
		lst = lst->next;
	}
	return (0);
}

void		ft_write_input(t_lem *g)
{
	char 	*line;
	t_input *start;

	g->input = (t_input*)malloc(sizeof(t_input));
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

void		ft_print_input(t_lem *g)
{
	t_input *print;

	print = g->input;
	while (print->next != NULL)
	{
		ft_printf("%s\n", print->data);
		print = print->next;
	}
}

int			ft_check_input(t_lem *g)
{
	//if (!(g->flag_ants))
	//	return (ft_error(1));
	if (!(g->flag_start))
		return (ft_error(2));
	else if (!(g->flag_end))
		return (ft_error(3));
	return (0);
}

int			main(void)
{
	t_lem	*g;
	g = (t_lem*)malloc(sizeof(t_lem));
	ft_bzero(g, sizeof(t_lem));
	ft_write_input(g);
	if (ft_parse_input(g))
		return (1);
	if (ft_check_input(g))
		return (1);
	//write(1, "1\n", 2);
	ft_print_input(g);
	//add a function where to delete all data and free lists
	//write (1, "11\n", 3);
	return (0);
}
