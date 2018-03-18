/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 13:06:11 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/30 17:50:28 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		set_value(t_room *room, t_tools *tools)
{
	int		area;
	t_room	*room_in_pipe;
	t_pipe	*temp_pipe;

	area = 0;
	room_in_pipe = NULL;
	room = room->begin;
	while (room && room->value)
	{
		if (room->value > area)
			area++;
		temp_pipe = room->pipes_begin;
		while (temp_pipe)
		{
			room_in_pipe = temp_pipe->room;
			temp_pipe = temp_pipe->next;
			if (!room_in_pipe->value && (room_in_pipe->value = area + 1))
				insert_room(room, room_in_pipe);
		}
		room = room->next;
	}
	return (1);
}

int		room_has_choice(t_room *begin, int value, char *str)
{
	t_pipe	*browse;

	if (!begin)
		return (0);
	browse = begin->pipes_begin;
	while (browse)
	{
		if ((browse->room->value == -2) || ((browse->room->value != -1)
		&& browse->room->value >= value && ft_strcmp(browse->room->name, str)))
			return (1);
		browse = browse->next;
	}
	return (0);
}

int		sort_pipes(t_room *begin, char *str)
{
	t_room		*min_value;
	t_pipe		*temp_pipe;

	if (!begin || !begin->pipes_begin || begin->taken)
		return (begin && begin->value == -2 ? 1 : -1);
	begin->taken = 1;
	min_value = NULL;
	temp_pipe = begin->pipes_begin;
	while (temp_pipe)
	{
		if (temp_pipe->room->value == -2 || (temp_pipe->room->value > 0 &&
	!temp_pipe->room->taken && (!min_value || (room_has_choice(temp_pipe->room,
begin->value, begin->name) && (min_value->value >= temp_pipe->room->value)))))
			min_value = temp_pipe->room;
		temp_pipe = temp_pipe->next;
	}
	if (min_value)
	{
		min_value->value > 0 ? min_value->value = begin->value + 1 : 0;
		delete_useless_pipes(begin, str, 0);
		begin->taken = sort_pipes(min_value, begin->name);
	}
	return (begin->taken = (begin->taken > 0 && min_value) ? 1 : -1);
}

int		find_best_paths(t_tools *tools)
{
	t_pipe	*p_begin;
	int		i;

	i = 0;
	p_begin = tools->end->pipes_begin;
	tools->begin->taken++;
	tools->end->taken++;
	while (p_begin)
	{
		p_begin->room->value = 1;
		sort_pipes(p_begin->room, tools->end->name);
		p_begin = p_begin->next;
	}
	return (1);
}
