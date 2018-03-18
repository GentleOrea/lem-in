/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_erase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:51:34 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/31 15:01:40 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

t_room		*init_room(char *name)
{
	t_room	*room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	room->name = ft_strdup(name);
	room->pipes_begin = NULL;
	room->taken = 0;
	room->ant_in = 0;
	room->value = 0;
	room->area = 0;
	room->next = NULL;
	room->prev = NULL;
	room->pipes = NULL;
	room->begin = NULL;
	return (room);
}

int			add_room(t_room *room, char *name)
{
	t_room	*temp;

	if (!room)
		return (-1);
	temp = room->begin ? room->begin : room;
	while (temp->next && ft_strcmp(temp->next->name, name))
		temp = temp->next;
	if (!ft_strcmp(temp->name, name)
	|| (temp->next && !ft_strcmp(temp->name, name)))
		return (1);
	if (!temp->name)
	{
		temp->begin = temp;
		temp->name = ft_strdup(name);
		return (1);
	}
	else if (!(temp->next = init_room(name)))
	{
		erase_rooms(temp);
		return (-1);
	}
	temp->next->prev = temp;
	temp->next->begin = temp->begin;
	return (1);
}

int			init_pipe(t_room *toadd, t_room *room)
{
	t_pipe *temp;

	if (!room || !toadd)
		return (-1);
	if (!room->pipes)
	{
		if (!(room->pipes = (t_pipe*)(malloc(sizeof(t_pipe)))))
			return (-1);
		room->pipes->room = toadd;
		room->pipes_begin = room->pipes;
		room->pipes->next = NULL;
		room->pipes->prev = NULL;
		return (1);
	}
	temp = room->pipes_begin;
	while (temp->next)
		temp = temp->next;
	if (!(temp->next = (t_pipe*)(malloc(sizeof(t_pipe)))))
		return (-1);
	temp->next->prev = temp;
	temp->next->room = toadd;
	temp->next->next = NULL;
	return (1);
}

int			add_pipe(t_room *room, char **tab)
{
	t_room	*room2;
	t_room	*room1;

	room1 = search_room(tab[0], room);
	room2 = search_room(tab[1], room);
	return ((init_pipe(room1, room2) - init_pipe(room2, room1)) ? -1 : 1);
}

t_tools		*init_tools(void)
{
	t_tools *tools;

	if (!(tools = (t_tools*)malloc(sizeof(t_tools))))
		return (NULL);
	tools->begin = NULL;
	tools->end = NULL;
	tools->touch_down = -1;
	tools->ant_max = -1;
	return (tools);
}
