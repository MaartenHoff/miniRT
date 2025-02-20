/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:43:14 by adiler            #+#    #+#             */
/*   Updated: 2025/02/20 18:25:57 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl	*create_new_node(char *buffer, int start, int len)
{
	char		*line;
	t_gnl		*new_node;
	int			i;

	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[start + i];
		i++;
	}
	line[i] = 0;
	new_node = malloc(sizeof(t_gnl));
	if (!new_node)
	{
		free(line);
		return (NULL);
	}
	new_node->line = line;
	new_node->next = NULL;
	return (new_node);
}

t_gnl	*split_and_store_line(t_gnl **head, char *buffer)
{
	size_t		i;
	t_gnl		*new_node;
	size_t		start;
	size_t		len;

	i = 0;
	while (buffer[i])
	{
		start = i;
		while (buffer[i] && buffer[i] != '\n')
			i++;
		len = i - start;
		if (len > 0 || buffer[i] == '\n')
		{
			if (buffer[i] == '\n')
				len++;
			new_node = create_new_node(buffer, start, len);
			if (!new_node)
				return (NULL);
			gnl_lstadd_back_c(head, new_node);
		}
		if (buffer[i])
			i++;
	}
	return (new_node);
}

int	read_split_and_store_line(int fd, t_gnl **head)
{
	int		bytes_read;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buf);
		if (bytes_read == 0)
			return (0);
		else
			return (-1);
	}
	buf[bytes_read] = '\0';
	if (!split_and_store_line(head, buf))
	{
		free(buf);
		return (-1);
	}
	free(buf);
	return (bytes_read);
}

char	*pop_and_join(t_gnl **head, char *line)
{
	t_gnl		*first;
	char		*temp_line;
	char		*new_line;

	if (head == NULL || *head == NULL)
		return (line);
	first = *head;
	temp_line = first->line;
	*head = first->next;
	free(first);
	new_line = gnl_strjoin(line, temp_line);
	free(line);
	free(temp_line);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static t_gnl		*head;
	char				*line;
	int					read_result;

	line = NULL;
	while (1)
	{
		if (!head)
		{
			read_result = read_split_and_store_line(fd, &head);
			handle_read_result(read_result, &head, &line);
			if (read_result == 0)
				return (line);
		}
		line = pop_and_join(&head, line);
		if (line == NULL || gnl_strchr(line, '\n'))
			break ;
	}
	return (line);
}
