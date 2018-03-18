/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:56:35 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/30 19:03:12 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int main(int ac, char **av)
{
	char *line;
	int fd = open(av[1], O_RDONLY);
	while (get_next_line_lst(fd, &line) > 0)
	{
		ft_printf("%s\n",line);
		ft_memdel((void**)&line);
	}
	return (0);
}
