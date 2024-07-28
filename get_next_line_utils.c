/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: largenzi <largenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:13:57 by largenzi          #+#    #+#             */
/*   Updated: 2024/03/02 21:24:44 by largenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	size_malloc;
	char	*new;
	char	*initial;

	size_malloc = (ft_strlen(s) + 1) * sizeof(char);
	new = malloc(size_malloc);
	if (new == NULL)
	{
		return (NULL);
	}
	else
		initial = new;
	while (*s != '\0')
	{
		*new = *s;
		new++;
		s++;
	}
	*new = '\0';
	new = initial;
	return (new);
}

char	*ft_strndup(const char *s, size_t len)
{
	size_t	size_malloc;
	char	*new;
	char	*initial;
	size_t	i;

	size_malloc = (len + 1) * sizeof(char);
	new = malloc(size_malloc);
	if (new == NULL)
	{
		return (NULL);
	}
	else
		initial = new;
	i = 0;
	while (i < len)
	{
		*new = *s;
		new++;
		s++;
		i++;
	}
	*new = '\0';
	new = initial;
	return (new);
}

size_t	ft_strlen(const char *s)
{
	const char	*initial;
	size_t		count;

	initial = s;
	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	s = initial;
	return (count);
}

char	*ft_strjoin(char *initial_string, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*joint_str;

	if (buffer == NULL)
		return (NULL);
	if (initial_string == NULL)
		initial_string = "";
	joint_str = malloc((ft_strlen(initial_string) + ft_strlen(buffer) + 1));
	if (joint_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (initial_string != NULL)
	{
		while (initial_string[i] != '\0')
		{
			joint_str[i] = initial_string[i];
			i++;
		}
	}
	while (buffer[j] != '\0')
		joint_str[i++] = buffer[j++];
	joint_str[ft_strlen(initial_string) + ft_strlen(buffer)] = '\0';
	return (joint_str);
}
