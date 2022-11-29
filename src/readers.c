/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:42:12 by llord             #+#    #+#             */
/*   Updated: 2022/11/29 12:58:55 by llord            ###   ########.fr       */
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
	while (++i < md->char_limit && fd)
	{
		if (0 < read(fd, c, 1))
			md->levels[md->lvl_c][i] = c[0];
		else
			break ;
	}
	free(c);
	if (fd < 0 || md->char_limit <= i)
		return (STATE_ERR_FILE);
	//printf("  Extracted level #%i as :\n\n%s\n", md->lvl_c, md->levels[md->lvl_c]);			//REMOVE ME
	return (STATE_RETRYING);
}
