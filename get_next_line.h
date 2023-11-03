/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:55:51 by njeanbou          #+#    #+#             */
/*   Updated: 2023/11/02 17:27:36 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
int		found_newline(t_list *temp);
t_list	*ft_last(t_list *temp);
void	generate_line(char **line, t_list *temp);
size_t	ft_strlen(const char *str);
void	read_to_temp(int fd, t_list **temp);
void	add_temp(t_list **temp, char *buffer, int nbread);
void	extract_line(t_list *temp, char **line);
void	clean_temp(t_list **temp);
void	free_temp(t_list *temp);

#endif