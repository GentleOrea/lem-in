/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:14:18 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/30 17:35:55 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		sort_room(t_tools *tools, int mode)
{
	t_room *temp;
	t_room *prev;

	if (mode > 1)
		return (1);
	temp = tools->begin->next;
	while ((temp->next) || (mode && temp->next))
		if (temp->next->value >= 0 && temp->value >= 0 &&
			((!mode && temp->next->area < temp->area) || (mode && temp->area
				== temp->next->area && temp->next->value < temp->value)))
		{
			prev = temp->prev;
			pop_from_list(temp);
			temp->prev = temp->next;
			temp->next = temp->next->next;
			temp->next ? temp->next->prev = temp : 0;
			temp->prev ? temp->prev->next = temp : 0;
			temp = tools->begin->next;
		}
		else
			temp = temp->next;
	sort_room(tools, ++mode);
	return (0);
}

int		set_first_rooms(t_room *room)
{
	t_pipe *temp;

	if (!room || !room->pipes_begin)
		return (0);
	temp = room->pipes_begin;
	while (temp->next)
	{
		if (temp->next->room->value < temp->room->value)
		{
			if (temp == room->pipes_begin)
				room->pipes_begin = temp->next;
			pop_pipe(temp);
			temp->prev = temp->next;
			temp->next = temp->next->next;
			temp->next ? temp->next->prev = temp : 0;
			temp->prev->next = temp;
			temp = room->pipes_begin;
		}
		else
			temp = temp->next;
	}
	return (0);
}

int		set_priority(t_room *room, int area, int is_begin)
{
	t_pipe	*begin;

	if (!room || !room->begin || (!is_begin && room->value < 0))
		return (0);
	if (is_begin)
	{
		begin = room->pipes_begin;
		while (begin->next)
			begin = begin->next;
		area = begin->room->value + 1;
	}
	begin = room->pipes_begin;
	while (begin)
	{
		if (begin->room->taken > 0)
		{
			begin->room->area = area;
			set_priority(begin->room, area - 1, 0);
		}
		begin = begin->next;
	}
	return (0);
}

int		set_begin_and_end(t_room *room, t_tools *tools)
{
	t_room *set_begin;

	if (!tools->begin || !tools->begin->pipes_begin
			|| !tools->end || !tools->end->pipes_begin)
		return (0);
	tools->begin->value = -2;
	tools->end->value = -1;
	set_begin = tools->begin;
	if (ft_strcmp(tools->begin->name, room->begin->name))
	{
		pop_from_list(tools->begin);
		room->begin->prev = tools->begin;
		tools->begin->next = room->begin;
		tools->begin->prev = NULL;
		tools->begin->begin = tools->begin;
		while ((set_begin = set_begin->next))
			set_begin->begin = tools->begin;
	}
	if (!ft_strcmp(tools->end->name, get_end(room)->name))
		return (1);
	pop_from_list(tools->end);
	tools->end->prev = get_end(room);
	get_end(room)->next = tools->end;
	tools->end->next = NULL;
	return (1);
}
