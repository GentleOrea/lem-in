/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 12:35:25 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/31 14:24:48 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/includes/libft.h"

typedef struct	s_room t_room;

typedef struct	s_pipe
{
	t_room	*room;
	struct s_pipe	*next;
	struct s_pipe	*prev;
}				t_pipe;

struct			s_room
{
	char	*name;
	int		area;
	int		ant_in;
	int		value;
	int		taken;
	t_pipe	*pipes;
	t_pipe	*pipes_begin;
	char	padding[4];
	struct s_room	*next;
	struct s_room	*prev;
	struct s_room	*begin;
};

typedef struct		s_tools
{
	t_room		*end;
	t_room		*begin;
	int		touch_down;
	int		ant_max;
}					t_tools;

int			there_is_an_error(t_room *room, t_tools *tools);
t_tools		*init_tools(void);
void		erase_global(t_room *room, t_tools *tools);

t_room		*init_room(char *name);
int			add_room(t_room *room, char *name);
void		erase_room(t_room *room);
void		erase_rooms(t_room *room);
void		pop_from_list(t_room *room);
t_room		*search_room(char *str, t_room *room);
t_room		*get_end(t_room *room);
void		insert_room(t_room *room1, t_room *room2);

int			add_pipe(t_room *room, char **tab);
int			init_pipe(t_room *toadd, t_room *room);
int			delete_useless_pipes(t_room *room, char *str, int mode);
void		erase_pipes(t_room *room);
void		pop_pipe(t_pipe *pipe);
void		erase_pipe(t_pipe *pipe);

int			main_parser(t_room *room, t_tools *tools);
int			there_is_a_path(t_room *room);
int			parse_room_and_pipe(char *str, t_room *room, int mode);
int			parse_command(char *str, t_room *room, t_tools *tools, int mode);

int			set_begin_and_end(t_room *room, t_tools *tools);
int			sort_pipes(t_room *room, char *str);
int			find_best_paths(t_tools *tools);
int			set_value(t_room *room, t_tools *tools);
int			sort_room(t_tools *tools, int mode);
int			set_priority(t_room *room, int area, int is_begin);
int			set_first_rooms(t_room *room);

void		print_paths(t_tools *tools);
void		ant_start(t_tools *tools);
void		ant_rush(t_tools *tools, t_room *room);

int			room_has_choice(t_room *room, int value, char *str);

void		print_room(t_room *room);
void		print_swap(t_room *room1, t_room *room2);
void		debug(t_room *room);
#endif
