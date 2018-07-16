/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:26:47 by alikhtor          #+#    #+#             */
/*   Updated: 2018/07/16 17:26:49 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/lemin.h"

static int  ft_check_ants(t_lem *g)
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

static int  ft_check_input(t_lem *g)
{
    if (!(g->flag_start))
        return (ft_error(2));
    else if (!(g->flag_end))
        return (ft_error(3));
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
        if (g->input->next != NULL)
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
    fd = open("/Users/alikhtor/Desktop/lem_in_github/test", O_RDONLY);
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