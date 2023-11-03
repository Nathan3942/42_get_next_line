/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:56:23 by njeanbou          #+#    #+#             */
/*   Updated: 2023/11/02 17:27:17 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Cherche '\n' pour la fin de ligne
int	found_newline(t_list *temp)
{
	int		i;
	t_list	*current;

	if (temp == NULL)
		return (0);
	current = ft_last(temp);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

//Renvoie un pointeur vers le derrnier element de temp
t_list	*ft_last(t_list *temp)
{
	t_list	*current;

	current = temp;
	while (current && current->next)
		current = current->next;
	return (current);
}

//calcule le nombre de caractere dans la ligne avec '\n' et malloc
void	generate_line(char **line, t_list *temp)
{
	int	i;
	int	len;

	len = 0;
	while (temp)
	{
		i = 0;
		while (temp->content[i])
		{
			if (temp->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		temp = temp->next;
	}
	*line = (char *)malloc((len + 1) * sizeof(char));
}

void	free_temp(t_list *temp)
{
	t_list	*current;
	t_list	*next;

	current = temp;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}