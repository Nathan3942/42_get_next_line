/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:44:30 by njeanbou          #+#    #+#             */
/*   Updated: 2023/11/08 03:05:46 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("read_error.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line)
			printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	return (0);
}
