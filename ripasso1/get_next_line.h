#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
char	*ft_read_to_left_str(int fd, char *left_str);
char	*ft_strchr(char *s, char c);
char	*ft_strjoin(char *left_str, char *buff);
int		ft_strlen(char *s);
char	*ft_strdup(char *s);
//char	*ft_strndup(char *s, int len);

#endif
