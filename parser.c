/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 13:14:27 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/31 15:13:26 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		there_is_a_path(t_room *begin)
{
	t_pipe *pbegin;

	if (!begin)
		return (0);
	pbegin = begin->pipes_begin;
	while (pbegin && pbegin->room->taken < 1)
		pbegin = pbegin->next;
	return (pbegin ? 1 : 0);
}

int		there_is_an_error(t_room *room, t_tools *tools)
{
	erase_global(room, tools);
	ft_printf("ERROR\n");
	return (1);
}

int		parse_command(char *str, t_room *room, t_tools *tools, int mode)
{
	int			value;
	t_room		*temp;

	value = 0;
	if (!ft_strcmp(&str[2], "start"))
		value = 0;
	else if (!ft_strcmp(&str[2], "end"))
		value = 1;
	else
		return (mode);
	if (get_next_line(0, &str) < 0
	|| (mode = parse_room_and_pipe(str, room, mode)) < 0)
		return (-1);
	temp = get_end(room);
	if (!*temp->name || ft_isin(*temp->name, "#L"))
		return (-1);
	if (!value)
		tools->begin = temp;
	else
		tools->end = temp;
	ft_printf("%s\n", str);
	ft_memdel((void**)&str);
	return (mode);
}

int		parse_room_and_pipe(char *str, t_room *room, int mode)
{
	char	**tab;
	char	c;
	int		occ;
	int		i;

	i = 1;
	c = (mode < 2) ? ' ' : '-';
	occ = (mode < 2) ? 2 : 1;
	if (mode > 2 || mode < 0 || (mode != 1 && ft_occur_in(str, c) != occ))
		return (-1);
	else if ((mode == 1 && ft_occur_in(str, c) != occ)
			|| (mode < 2 && ft_isin('-', str)))
		return (parse_room_and_pipe(str, room, ++mode));
	tab = ft_strsplit(str, c);
	while (tab && mode < 2 && tab[i] && ft_str_isdigit(tab[i]))
		i++;
	if (!tab || (!mode && --i != occ) || (mode == 2
		&& (!search_room(tab[0], room) || !search_room(tab[1], room))))
	{
		ft_free_dblechar_tab(tab);
		return (-1);
	}
	mode = (mode < 2) ? add_room(room, tab[0]) : add_pipe(room, tab);
	ft_free_dblechar_tab(tab);
	return (mode ? mode : ++mode);
}

int		main_parser(t_room *room, t_tools *tools)
{
	char	*temp;
	int		mode;
	int		ret;

	ret = 1;
	mode = 0;
	if (get_next_line(0, &temp) <= 0 || !ft_str_isdigit(temp) || !ft_atoi(temp))
		ret = 0;
	ret ? tools->ant_max = ft_atoi(temp) : 0;
	ret ? ft_printf("%s\n", temp) : 0;
	ft_memdel((void**)&temp);
	while (mode >= 0 && ret && get_next_line(0, &temp) > 0)
	{
		ret ? ft_printf("%s\n", temp) : 0;
		if (*temp && *temp == '#' && temp[1] && temp[1] == '#')
			mode = (parse_command(temp, room, tools, mode));
		else if (!*temp || *temp == 'L' || (*temp != '#'
				&& 0 > (mode = parse_room_and_pipe(temp, room, mode))))
			ret = 0;
		ft_memdel((void**)&temp);
	}
	ft_memdel((void**)&temp);
	return (!(mode < 0 || mode > 2 || !ret));
}
