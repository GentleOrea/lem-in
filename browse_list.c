/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:24:19 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/30 17:34:00 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void		pop_from_list(t_room *room1)
{
	if (room1->next)
		room1->next->prev = room1->prev;
	if (room1->prev)
		room1->prev->next = room1->next;
}

void		pop_pipe(t_pipe *pipe)
{
	if (pipe->next)
		pipe->next->prev = pipe->prev;
	if (pipe->prev)
		pipe->prev->next = pipe->next;
}

void		insert_room(t_room *room1, t_room *room2)
{
	t_room	*temp;

	if (!room1 || !room2 || !ft_strcmp(room1->name, room2->name))
		return ;
	pop_from_list(room2);
	temp = room1;
	while (temp->next && temp->next->value > 0)
		temp = temp->next;
	if (temp->next)
		temp->next->prev = room2;
	room2->next = temp->next;
	temp->next = room2;
	room2->prev = temp;
}

t_room		*get_end(t_room *room)
{
	t_room *temp;

	temp = NULL;
	if (!room)
		return (NULL);
	temp = room->begin;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_room		*search_room(char *str, t_room *room)
{
	t_room *index;

	index = room->begin;
	while (index)
	{
		if (!ft_strcmp(index->name, str))
			return (index);
		index = index->next;
	}
	return (NULL);
}
