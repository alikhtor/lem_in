/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 15:10:58 by alikhtor          #+#    #+#             */
/*   Updated: 2018/08/08 17:00:47 by alikhtor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libftprintf/includes/ft_printf.h"

typedef struct			s_way
{
	int					end;
	int					used;
	char				*name;
	struct s_way		*next;
}						t_way;

typedef struct			s_ant
{
	int					ant_num;
	t_way				*room;
	struct s_ant		*next;
}						t_ant;

typedef struct			s_input
{
	char				*data;
	struct s_input		*next;
}						t_input;

typedef struct			s_kid_rooms
{
	char				*kid_name;
	struct s_kid_rooms	*next;
}						t_kid_rooms;

typedef struct			s_rooms
{
	char				*name;
	char				*type;
	char				*parent;
	int					seen;
	int					x;
	int					y;
	t_kid_rooms			*kid;
	struct s_rooms		*next;
}						t_rooms;

typedef struct			s_links
{
	char				*l1;
	char				*l2;
	int					used;
	struct s_links		*next;
}						t_links;

typedef struct			s_lem
{
	t_input				*input;
	t_rooms				*room;
	t_links				*link;
	t_way				*way;
	t_ant				*ant;
	int					ants;
	int					flag_start;
	int					flag_end;
	int					flag_link;
}						t_lem;

int						ft_error(int error_index);
void					ft_start(t_lem *g, t_input *i);
void					ft_end(t_lem *g, t_input *i);
void					ft_room(t_lem *g, t_input *in);
int						ft_check_link(t_lem *g);
int						ft_link(t_lem *g);
void					ft_add_room_type(t_lem *g, char *room_type);
void					ft_room_or_link_or_comment(t_lem *g, t_input *i);
void					ft_parse_and_check_input(t_lem *g,
		t_input *i, t_rooms *r);
void					ft_write_input(t_lem *g);
void					ft_print_input(t_lem *g,
		t_input *print, int index);
void					ft_check_room_coordinates_and_names(t_lem *g,
		t_input *i, t_rooms *r);
int						ft_p_and_k(t_lem *g);
void					ft_start_kids(t_lem *g, t_rooms *r_start,
		t_links *l_start);
void					ft_move_ants(char **the_way, t_lem *g);
char					**ft_find_the_way(t_rooms *r_start);
void					ft_free_way_str(char **the_way);
void					ft_find_identical_links(t_lem *g);

#endif
