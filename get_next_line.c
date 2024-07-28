/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: largenzi <largenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:11:53 by largenzi          #+#    #+#             */
/*   Updated: 2024/03/02 21:24:28 by largenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*saved_string;
	char		*line_to_return;
	char		*tmp;
	static int	the_end;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (the_end == 1)
		return (NULL);
	saved_string = read_update_static(fd, saved_string);
	if (saved_string == NULL)
		return (NULL);
	line_to_return = get_line_fm_static(saved_string);
	tmp = update_saved_string_before_return(saved_string);
	free(saved_string);
	if (tmp != NULL)
		saved_string = tmp;
	else
		the_end = 1;
	return (line_to_return);
}

char	*update_saved_string_before_return(char *saved_string)
{
	char	*new_saved_string;
	int		for_strdup;

	for_strdup = 0;
	while (saved_string[for_strdup] != '\n' && saved_string[for_strdup] != '\0')
		for_strdup++;
	if (saved_string[for_strdup] == '\0')
		return (NULL);
	new_saved_string = ft_strdup(saved_string + for_strdup + 1);
	if (new_saved_string == NULL)
		return (NULL);
	return (new_saved_string);
}

char	*read_update_static(int fd, char *saved_string)
{
	int		n;
	char	*buffer;
	char	*tmp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	n = 1;
	while (n > 0 && ft_strchr(saved_string, '\n') == NULL)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
			return (free(buffer), NULL);
		buffer[n] = '\0';
		tmp = ft_strjoin(saved_string, buffer);
		free(saved_string);
		saved_string = ft_strdup(tmp);
		if (saved_string == NULL)
			return (free(tmp), NULL);
		free(tmp);
	}
	return (free(buffer), saved_string);
}

char	*get_line_fm_static(char *saved_string)
{
	int		i;
	char	*str_to_return;

	i = 0;
	if (saved_string[i] == '\0')
		return (NULL);
	while (saved_string[i] != '\n' && saved_string[i] != '\0')
		i++;
	str_to_return = ft_strndup(saved_string, (size_t)i + 1);
	if (str_to_return == NULL)
		return (NULL);
	return (str_to_return);
}
