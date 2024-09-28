#include "get_next_line.h"


char	*get_next_line(int fd)
{
	static char	*saved_str;
	char		*line_to_return;
	char		*tmp;
	static int	the_end;
	/*---reading---*/
	int read_bytes = 0;
	char *buffer = NULL;
	/*------*/
	char	*joint_str = NULL;
	
/*-----PART ONE-----*/
	/*---first check ---*/
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (the_end == 1)
		return (NULL);

	/*---create buffer---*/
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	
	/*---while to read up to \n*/
	read_bytes = 1; //to consent to start while loop
	while (read_bytes > 0 && ft_strchr(saved_str, '\n') == NULL)
	{
		/*fill buffer*/
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0) //error
			return(free(buffer), NULL);
		buffer[read_bytes] = '\0'; //close the buffer
		
		/*first time for saved_str*/
		if (saved_str == NULL) //at beginning saved_str is always NULL
		{
			saved_str = (char *)malloc(1 * sizeof(char));
			if (saved_str == NULL)
				return (NULL);
			saved_str[0] = '\0';
		}
		
		/*join saved and filled_buffer*/
		joint_str = ft_strjoin(saved_str, buffer); //join new_string
		if (joint_str == NULL)
		{	
			free(saved_str);
			free(buffer);
			return(NULL);
		}

		/*update saved_str*/
		free(saved_str);
		saved_str = NULL;
		saved_str = ft_strdup(joint_str); //update saved string
		if (saved_str == NULL)
		{
			free(buffer);
			free(joint_str);
			return (NULL);
		}
		free(joint_str);
	}

	/*---after while free buffer---*/
	free(buffer); 

/*PART TWO*/
	/*what to return*/
	int		i;
	line_to_return = NULL;
	i = 0;
	if (saved_str[i] == '\0')
		line_to_return =  NULL;
	else
	{
		while (saved_str[i] != '\n' && saved_str[i] != '\0')
			i++;
		line_to_return = ft_strndup(saved_str, (size_t)i + 1);
	}

/****PART THREE****/
//	tmp = update_saved_string_before_return(saved_str);

//	char	*new_saved_string;
//	int		for_strdup;

	i = 0;
	while (saved_str[i] != '\n' && saved_str[i] != '\0')
		i++;

	if (saved_str[i] == '\0')
	{
		tmp = (NULL);
		free(saved_str);
		the_end = 1;
	}
	else
	{
		tmp  = ft_strdup(saved_str + i + 1);
		if (tmp == NULL)
		{
			free(saved_str);
			the_end = 1;
		}
		else
		{
			free(saved_str);
			saved_str = tmp;
		}
	}



/******************************************/
	//free(saved_str);
	//if (tmp != NULL)
	//	saved_str = tmp;
	//else
	//	the_end = 1;
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
