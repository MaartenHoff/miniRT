/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:40:31 by adiler            #+#    #+#             */
/*   Updated: 2025/02/20 18:25:30 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	char			*line;
	struct s_gnl	*next;
}					t_gnl;
void				*gnl_memcpy(void *dest, const void *src, size_t n);
char				*gnl_strchr(const char *s, int c);
char				*gnl_strjoin(char const *s1, char const *s2);
void				gnl_lstadd_back_c(t_gnl **lst, t_gnl *new_node);
void				handle_read_result(int result, t_gnl **head, 
						char **line);

#endif