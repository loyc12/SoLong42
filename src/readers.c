/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:42:12 by llord             #+#    #+#             */
/*   Updated: 2022/11/28 12:17:37 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	get_level(t_meta *md, char *path)
{
	char	*c;
	int		fd;
	int		i;

	md->levels[md->lvl_c] = ft_calloc(md->char_limit, sizeof(char *));
	i = -1;
	c = ft_calloc(1, sizeof(char *));
	fd = open(path, O_RDONLY);
	while (++i < md->char_limit)
	{
		if (0 < read(fd, c, 1))
			md->levels[md->lvl_c][i] = c[0];
		else
			break ;
	}
	free(c);
	if (md->char_limit <= i)
		return (STATE_ERR_FILE);
	//printf("  Extracted level #%i as :\n\n%s\n", md->lvl_c, md->levels[md->lvl_c]);			//REMOVE ME
	return (STATE_RETRYING);
}
