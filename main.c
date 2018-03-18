/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 15:14:04 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/31 15:15:01 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int	main(void)
{
	t_room	*room;
	t_tools	*tools;

	tools = NULL;
	tools = init_tools();
	room = init_room(NULL);
	if ((!(main_parser(room, tools)) || !(set_begin_and_end(room, tools)))
		&& there_is_an_error(room, tools))
		return (0);
	set_value(room, tools);
	set_first_rooms(tools->end);
	find_best_paths(tools);
	if (!(there_is_a_path(tools->begin)) && there_is_an_error(room, tools))
		return (0);
	set_first_rooms(tools->begin);
	set_priority(tools->begin, 0, 1);
	sort_room(tools, 0);
	tools->touch_down = tools->ant_max;
	ft_printf("\n");
	ant_start(tools);
	erase_global(room, tools);
	return (1);
}
