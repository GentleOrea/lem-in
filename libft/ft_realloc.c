/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:08:03 by ygarrot           #+#    #+#             */
/*   Updated: 2018/01/25 19:10:27 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void *buf;

	buf = NULL;
	if (!size && ptr)
	{
		ft_memdel((void**)&ptr);
		return (NULL);
	}
	else if (!ptr)
		return ((ptr = (void*)malloc(size * sizeof(char))) ? ptr : NULL);
	else
	{
		buf = ft_strdup(ptr);
		ft_memdel((void**)&ptr);
		if (!(ptr = (void*)malloc(size * sizeof(char))))
		{
			ft_memdel((void**)&buf);
			return (NULL);
		}
		ft_strcpy(ptr, buf);
		ft_memdel((void**)&buf);
	}
	return (ptr);
}
