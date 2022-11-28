/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_imports.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:42:12 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 12:07:09 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	*ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n--)
		*ptr++ = 0;
	return (s);
}

void	*ft_calloc(size_t count, size_t	size)
{
	void	*ptr;
	size_t	i;

	i = count * size;
	if (i == 0)
		i++;
	ptr = (void *)malloc(i);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, i);
	return (ptr);
}
