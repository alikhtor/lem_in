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

#ifndef __LEMIN_H__
# define __LEMIN_H__

# include "../libftprintf/includes/ft_printf.h"

typedef struct			s_input
{
	char				*data;
	struct s_input		*next;
}						t_input;

typedef struct			s_rooms
{
	char				*name;
	char				*type;
	char				*following;
	int					x;
	int 				y;
	struct s_rooms		*next;
}						t_rooms;

typedef struct			s_links
{
	//char				*previous;
	char				*current;
	char				*following;
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

#endif
