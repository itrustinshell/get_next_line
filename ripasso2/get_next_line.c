#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

/* Function to extract a substring ending with a newline */
char *nl_strdup(char *str_to_dup)
{
    int i = 0;
    char *str_to_ret;

    while (str_to_dup[i] != '\n')
        i++;
    str_to_ret = (char *)malloc((i + 2) * sizeof(char));
    if (!str_to_ret)
        return (NULL);
    i = 0;
    while (str_to_dup[i] != '\n')
    {
        str_to_ret[i] = str_to_dup[i];
        i++;
    }
    str_to_ret[i] = str_to_dup[i];
    i++;
    str_to_ret[i] = '\0';
    return str_to_ret;
}

/* Function to save the remainder of the string after the newline */
char *str_to_save(char *str_to_inspect)
{
    int i = 0;
    int k = 0;
    char *str_to_ret;

    while (str_to_inspect[i] != '\n')
        i++;
    i++; // Move past the newline
    while (str_to_inspect[i + k] != '\0')
        k++;
    str_to_ret = (char *)malloc((k + 1) * sizeof(char));
    if (!str_to_ret)
        return (NULL);
    k = 0;
    while (str_to_inspect[i + k] != '\0')
    {
        str_to_ret[k] = str_to_inspect[i + k];
        k++;
    }
    str_to_ret[k] = '\0';
    return str_to_ret;
}

/* Get the next line from file descriptor */
char *get_next_line(int fd)
{
    static char *static_str = NULL;
    char *line_to_return;
    char *tmp;
    char *buffer;
    int read_bytes;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    if (!static_str)
    {
        static_str = (char *)malloc(1 * sizeof(char));
        if (!static_str)
            return (NULL);
        static_str[0] = '\0';
    }

    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (free(static_str), NULL);

    read_bytes = 1;
    while (read_bytes > 0 && !ft_strchr(static_str, '\n'))
    {
        read_bytes = read(fd, buffer, BUFFER_SIZE);
        if (read_bytes < 0)
            return (free(buffer), NULL);
        buffer[read_bytes] = '\0';
        tmp = ft_strjoin(static_str, buffer);
        if (!tmp)
            return (free(buffer), NULL);
        free(static_str);
        static_str = tmp;
    }
    free(buffer);

    if (static_str[0] == '\0') // End of file
    {
        free(static_str);
        static_str = NULL;
        return (NULL);
    }

    if (ft_strchr(static_str, '\n'))
    {
        line_to_return = nl_strdup(static_str);
        tmp = str_to_save(static_str);
        free(static_str);
        static_str = tmp;
    }
    else
    {
        line_to_return = static_str;
        static_str = NULL;
    }

    return line_to_return;
}
/*
int main(void)
{
    int fd = open("./file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
*/
