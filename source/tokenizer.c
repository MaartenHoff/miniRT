/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maahoff <maahoff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:53:22 by maahoff           #+#    #+#             */
/*   Updated: 2025/02/20 18:47:03 by maahoff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	count_tokens(char *line)
{
	int	cnt;
	int	i;
	int	in_token;

	cnt = 0;
	i = 0;
	in_token = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
		{
			in_token = 0;
		}
		else if (!in_token)
		{
			cnt++;
			in_token = 1;
		}
		i++;
	}
	return (cnt);
}

void	free_tokens(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static char	*extract_token(char *line, int *pos)
{
	int		start;
	int		end;
	char	*token;

	start = *pos;
	while (line[*pos] && !is_whitespace(line[*pos]))
		(*pos)++;
	end = *pos;
	token = malloc(end - start + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, line + start, end - start + 1);
	return (token);
}

char	**tokenizer(char *line)
{
	char	**tokens;
	int		count;
	int		i;
	int		j;

	if (!line || !*line)
		return (NULL);
	count = count_tokens(line);
	tokens = malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (j < count)
	{
		while (is_whitespace(line[i]))
			i++;
		if (line[i])
		{
			tokens[j] = extract_token(line, &i);
			if (!tokens[j])
				return (free_tokens(tokens), NULL);
			j++;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}
