/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 19:20:49 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/30 17:42:50 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	erase_pipes(t_room *room)
{
	t_pipe		*delpipe;
	t_pipe		*pipe;

	if (!room || !room->pipes_begin)
		return ;
	pipe = room->pipes_begin;
	while (pipe)
	{
		delpipe = pipe;
		pipe = pipe->next;
		ft_memdel((void**)&delpipe);
	}
}

void	erase_room(t_room *room)
{
	if (!room)
		return ;
	erase_pipes(room);
	ft_memdel((void**)&room->name);
	ft_memdel((void**)&room);
}

void	erase_rooms(t_room *room)
{
	t_room		*temp_room;
	t_room		*delroom;

	if (!room)
		return ;
	temp_room = room->begin;
	while (temp_room)
	{
		delroom = temp_room;
		temp_room = temp_room->next;
		erase_room(delroom);
	}
}

int		delete_useless_pipes(t_room *room, char *str, int mode)
{
	t_pipe *pipe;
	t_pipe *todel;

	todel = NULL;
	if (!room || !room->pipes || !room->pipes_begin || room->value < 0)
		return (0);
	pipe = room->pipes_begin;
	while (pipe)
	{
		if (((mode && !ft_strcmp(pipe->room->name, str))
					|| (!mode && ft_strcmp(pipe->room->name, str))))
		{
			pop_pipe(pipe);
			if (!ft_strcmp(pipe->room->name, room->pipes_begin->room->name))
				room->pipes_begin = pipe->next;
			todel = pipe;
			pipe = todel->next;
			ft_memdel((void**)&todel);
		}
		else
			pipe = pipe->next;
	}
	return (1);
}

void	erase_global(t_room *room, t_tools *tools)
{
	erase_rooms(room);
	ft_memdel((void**)&tools);
}
