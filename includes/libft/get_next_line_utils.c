/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:05 by adiler            #+#    #+#             */
/*   Updated: 2025/02/20 18:26:16 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = dest;
	s = src;
	while (n > 0)
	{
		*(d++) = *(s++);
		n--;
	}
	return (dest);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	while (s1 && s1[len1])
		len1++;
	while (s2 && s2[len2])
		len2++;
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	gnl_memcpy(str, s1, len1);
	gnl_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

void	gnl_lstadd_back_c(t_gnl **lst, t_gnl *new_node)
{
	t_gnl	*current;

	if (lst == NULL)
		return ;
	else if (*lst == NULL)
		*lst = new_node;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	handle_read_result(int result, t_gnl **head, char **line)
{
	t_gnl	*tmp;

	if (result <= 0)
	{
		while (*head)
		{
			tmp = (*head)->next;
			free((*head)->line);
			free(*head);
			*head = tmp;
		}
		if (result == 0)
			return ;
		free(*line);
		*line = NULL;
	}
}
