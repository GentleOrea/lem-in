/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convuimax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 11:00:53 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/17 18:32:09 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*convuimo(uintmax_t nb)
{
	return (ft_uimaxtoabase(nb, 8));
}

char	*convuimx(uintmax_t nb)
{
	return (ft_uimaxtoabase(nb, 16));
}

char	*convuim(uintmax_t nb)
{
	return (ft_uimaxtoabase(nb, 10));
}

char	*convim(intmax_t nb)
{
	return (ft_imaxtoabase(nb, 10));
}
