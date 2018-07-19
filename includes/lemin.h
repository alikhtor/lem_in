/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 15:10:58 by alikhtor          #+#    #+#             */
/*   Updated: 2018/07/10 17:11:47 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEM_IN_H__
# define __LEM_IN_H__

# include "../libftprintf/includes/ft_printf.h"

typedef struct			s_input
{
	char				*data;
	struct s_input		*next;
}						t_input;

typedef struct          s_kid_rooms
{
    char                *kid_name;
    struct s_kid_rooms  *next;
}                       t_kid_rooms;

typedef struct			s_rooms
{
	char				*name;
	char				*type;
    char                *parent;
    int                 seen;
	int					x;
	int 				y;
    t_kid_rooms         *kid;
	struct s_rooms		*next;
}						t_rooms;

typedef struct			s_links
{
	char				*l1;
	char				*l2;
	struct s_links		*next;
}						t_links;

typedef struct	s_lem
{
	t_input		*input;
	t_rooms		*room;
	t_links		*link;
	int 		ants;
	int			flag_start;
	int			flag_end;
}				t_lem;

int			ft_error(int error_index);
int 		ft_start(t_lem *g);
int 		ft_end(t_lem *g);
int         ft_room(t_lem *g);
int 		ft_link(t_lem *g);
void		ft_add_room_type(t_lem *g, char *room_type);
int         ft_room_or_link_or_comment(t_lem *g);
int			ft_parse_and_check_input(t_lem *g);
void		ft_write_input(t_lem *g);
void		ft_print_input(t_input *print);
int         ft_check_room_coordinates_and_names(t_rooms *room_a);

#endif
