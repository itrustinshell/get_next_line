#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char *ft_strchr(const char *s, int c)
{
    if (!s)
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

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

char *ft_strjoin(char *initial_string, char *buffer_to_add)
{
    int len_initial = ft_strlen(initial_string);
    int len_buffer = ft_strlen(buffer_to_add);
    char *joint_str = (char *)malloc((len_initial + len_buffer + 1) * sizeof(char));

    if (!joint_str)
        return (NULL);

    int i = 0;
    while (i < len_initial)
    {
        joint_str[i] = initial_string[i];
        i++;
    }

    int j = 0;
    while (j < len_buffer)
    {
        joint_str[i + j] = buffer_to_add[j];
        j++;
    }

    joint_str[i + j] = '\0';
    return joint_str;
}

