/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 09:45:33 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/30 17:41:25 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	print_paths(t_tools *tools)
{
	t_room *begin;

	begin = tools->begin;
	while (begin)
	{
		if (begin->ant_in > 0 && begin->value >= 0)
			ft_printf("L%d-%s ", begin->ant_in, begin->name);
		begin = begin->next;
	}
	ft_printf("\n");
}

void	ant_start(t_tools *tools)
{
	int		ant;
	t_pipe	*pipe;

	ant = 1;
	while (tools->touch_down > 0)
	{
		pipe = tools->begin->pipes_begin;
		while (pipe)
		{
			if (pipe->room->taken > 0)
			{
				pipe->room->value >= 0 ? ant_rush(tools, pipe->room) : 0;
				pipe->room->ant_in = ant <= tools->ant_max ? ant : 0;
				ant = ant <= tools->ant_max ? ++ant : ant;
				if (pipe->room->value == -1 && pipe->room->ant_in
				&& ft_printf("L%d-%s ", pipe->room->ant_in, pipe->room->name))
					tools->touch_down--;
				if (!pipe->room->ant_in && pipe->room->value >= 0)
					pipe->room = pipe->room->pipes_begin->room;
			}
			pipe = pipe->next;
		}
		print_paths(tools);
	}
}

void	ant_rush(t_tools *tools, t_room *room)
{
	t_pipe *pipe;

	pipe = room->pipes_begin;
	if (room->pipes_begin->room->value < 0 && room->ant_in)
	{
		tools->touch_down--;
		ft_printf("L%d-%s ", room->ant_in, room->pipes_begin->room->name);
	}
	if (room->value >= 0 && room->pipes_begin->room->ant_in)
		ant_rush(tools, room->pipes_begin->room);
	room->value > 0 ? room->pipes_begin->room->ant_in = room->ant_in : 0;
}
