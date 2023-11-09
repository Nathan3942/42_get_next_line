/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:56:05 by njeanbou          #+#    #+#             */
/*   Updated: 2023/11/09 04:35:45 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static t_list	*stock = NULL;
	char			*line;
	int				i;

	i = 0;
	line = NULL;
	if ((read(fd, 0, 0) < 0) || fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_lstclear(&stock, free);
		return (NULL);
	}
	if (BUFFER_SIZE > 0)
	{
		read_and_stock(fd, &stock);
		creat_line(stock, &line);
		refactor_line(&stock);
	}
	return (line);
}

void	read_and_stock(int fd, t_list **stock)
{
	int		nbread;
	char	*buffer;
	t_list	*new;

	nbread = 0;
	while (!found_newline(*stock))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		nbread = (int)read(fd, buffer, BUFFER_SIZE);
		if (buffer == NULL || nbread == 0)
		{
			free(buffer);
			return ;
		}
		new = ft_lstnew(buffer);
		new->content[nbread] = '\0';
		ft_lstadd_back(stock, new);
	}
	return ;
}

int	found_newline(t_list *stock)
{
	int	i;

	i = 0;
	stock = ft_lstlast(stock);
	if (!stock)
		return (0);
	while (stock->content[i] != '\0')
	{
		if (stock->content[i] == '\n')
		{
			stock->length = ++i;
			return (1);
		}
		i++;
	}
	stock->length = i;
	return (0);
}

void	creat_line(t_list *stock, char **line)
{
	int		size;
	int		i;
	t_list	*temp;

	size = 0;
	temp = stock;
	while (temp)
	{
		size = size + temp->length;
		temp = temp->next;
	}
	if (size == 0)
		return ;
	*line = malloc((size + 1) * sizeof(**line));
	if (*line == NULL)
		return ;
	size = 0;
	while (stock && stock->content)
	{
		i = 0;
		while (stock->content[i] && i < stock->length)
			(*line)[size++] = stock->content[i++];
		stock = stock->next;
	}
	(*line)[size] = '\0';
}

void	refactor_line(t_list **stock)
{
	t_list	*temp;
	t_list	*new;
	char	*content;
	int		i;
	int		size;

	temp = ft_lstlast(*stock);
	if (!temp)
		return ;
	content = temp->content;
	size = temp->length;
	temp->content = NULL;
	ft_lstclear(stock, free);
	i = 0;
	if (content[size] != '\0')
	{
		while (content[size] != '\0')
			content[i++] = content[size++];
		content[i] = '\0';
		new = ft_lstnew(content);
		ft_lstadd_back(stock, new);
	}
	else
		free(content);
}
