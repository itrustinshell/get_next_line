#include "get_next_line.h"
/*
allora saved string è una statica non devi controllare qui se è null perhcè lo sara sicuramento
all'inizio....sempre! il controllo lo fai nello strjoin ma per allocre qualcosa che si leghi a qualcos'altro
 */
char	*get_raw_nlstr(int fd, char *saved_string)
{
	int		read_bytes;
	char	*buffer = NULL;
	char	*joint_str = NULL;
	char	*testing_str = NULL;
	
	testing_str = saved_string;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_bytes = 1; //to consent to start while loop
	while (read_bytes > 0 && ft_strchr(testing_str, '\n') == NULL)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0) //error
		{
			if (joint_str != NULL)
				free(joint_str);
			free(buffer);
			return NULL;
		}
		buffer[read_bytes] = '\0';
		joint_str = ft_strjoin(testing_str, buffer);
		if (joint_str == NULL)
		{
			free (buffer);
			return NULL;
		}
		free(testing_str); //attenzione che prima o poi saved_str sarà il risultato di un malloc, ovvero di questa funzione...quindi qui ad un certo punto bisognerà freeare.
		testing_str = NULL;
		testing_str = ft_strdup(joint_str);
		if (testing_str == NULL)
		{
			free(buffer);
			free(joint_str);
			return (NULL);
		}
		free(joint_str);
	}
	free(buffer);
	return (testing_str);
}

char	*get_line_fm_static(char *saved_string)
{
	int		i;
	char	*str_to_return;

	i = 0;
	if (saved_string[i] == '\0')
	{
		printf("heiiii\n");
		return (NULL);
	}
	while (saved_string[i] != '\n' && saved_string[i] != '\0')
		i++;
	str_to_return = ft_strndup(saved_string, (size_t)i + 1);
	if (str_to_return == NULL)
		return (NULL);
	return (str_to_return);
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
	saved_string = get_raw_nlstr(fd, saved_string);
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

/*
int main ()
{
	int fd = open("./file.txt", O_RDONLY);
	char *str = get_next_line(fd);
	char *we = get_next_line(fd);
	char *p = get_next_line(fd);
	printf("%s", str);
	printf("%s", we);
	printf("%s", p);
	free(str);
	free(we);
	free(p);
	close(fd);
	return (0);
}
*/
