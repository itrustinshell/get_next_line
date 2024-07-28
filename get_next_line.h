/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: largenzi <largenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:13:03 by largenzi          #+#    #+#             */
/*   Updated: 2024/03/02 21:24:26 by largenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
char	*ft_read_to_left_str(int fd, char *left_str);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *left_str, char *buff);
size_t	ft_strlen(const char *s);
char	*read_update_static(int fd, char *saved_string);
char	*get_line_fm_static(char *saved_string);
char	*update_saved_string_before_return(char *saved_string);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t len);

#endif