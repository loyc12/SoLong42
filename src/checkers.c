/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/02 14:01:33 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// checks if given board coordinates are valid
int	is_in_board(t_data *d, t_coords *bc)
{
	if (0 <= bc->x && bc->x <= d->max_bx)
		if (0 <= bc->y && bc->y <= d->max_by)
			return (1);
	return (0);
}

// checks if given window coordinates are valid
int	is_in_window(t_data *d, t_coords *wc)
{
	if (0 <= wc->x && wc->x <= d->max_wx)
		if (0 <= wc->y && wc->y <= d->max_wy)
			return (1);
	return (0);
}

//checks if 
int	is_valid(char *input)
{
	int		flag;
	char	c;
	int		i;

	i = -1;
	flag = 1;
	while (input[++i])
	{
		c = input[i];
		if (c == 'P')
			flag *= 2;
		else if (c == 'E')
			flag *= 3;
		else if (c == 'C')
			flag *= 5;
		else if (c != '0' && c != '1'&& c != '\n')
			return (0);
	}
	if (flag % 2 || flag % 3 || flag % 5)
		return (0);
	return (1);
}
