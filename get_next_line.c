/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:56:05 by njeanbou          #+#    #+#             */
/*   Updated: 2023/11/02 18:32:13 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*temp = NULL;
	char			*line;
	int				nbread;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	nbread = 1;
	line = NULL;
	// lire de fd et le mettre dans list 
	read_to_temp(fd, &temp);
	if (temp == NULL)
		return (NULL);
	// extraire de temp dans line
	extract_line(temp, &line);
	// clean temp
	clean_temp(&temp);
	if (line[0] == '\0')
	{
		free(temp);
		temp = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_to_temp(int fd, t_list **temp)
{
	char	*buffer;
	int		nbread;

	nbread = 1;
	while ((!found_newline(*temp)) && nbread != 0)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return ;
		nbread = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*temp == NULL && nbread == 0) || nbread == -1)
		{
			free(buffer);
			return ;
		}
		buffer[nbread] = '\0';
		add_temp(temp, buffer, nbread);
		free(buffer);
	}
}

//ajoue le contenu du buffer a la fin de temp
void	add_temp(t_list **temp, char *buffer, int nbread)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = malloc((nbread + 1) * sizeof(char));
	if (!new_node->content)
		return ;
	i = 0;
	while (buffer[i] && i < nbread)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*temp == NULL)
	{
		*temp = new_node;
		return ;
	}
	last = ft_last(*temp);
	last->next = new_node;
}

//extraire tout les caractere de temp pour les mettre dans la ligne sarretant apres le premier '\n'
void	extract_line(t_list *temp, char **line)
{
	int	i;
	int	j;

	if (temp == NULL)
		return ;
	generate_line(line, temp);
	if (*line == NULL)
		return ;
	j = 0;
	while (temp)
	{
		i = 0;
		while (temp->content[i])
		{
			if (temp->content[i] == '\n')
			{
				(*line)[j++] = temp->content[i];
				break ;
			}
			(*line)[j++] = temp->content[i++];
		}
		temp = temp->next;
	}
	(*line)[j] = '\0';
}

//fonction netoie temp pour que seul les caractere qui n'on pas ete renvoyé reste dans temp static
void	clean_temp(t_list **temp)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	size_t	j;

	clean_node = malloc(sizeof(t_list));
	if (!temp || !clean_node)
		return ;
	clean_node->next = NULL;
	last = ft_last(*temp);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	j = ft_strlen(last->content);
	clean_node->content = malloc(((j - i) + 1) * sizeof(char));
	if (!clean_node->content)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_temp(*temp);
	*temp = clean_node;
}

