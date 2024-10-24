#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

char *ft_strchr(char *str, char c)
{
	int i;

	i = 0;
	while(str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return str;
	else
		return NULL;
	return NULL;
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return i;

}


char *ft_strjoin(char *static_str, char *buffer)
{
	char *str_to_ret;
	int len;

	if (static_str == NULL || buffer == NULL)
		return NULL;
	len = ft_strlen(static_str) + ft_strlen(buffer) + 1;
	str_to_ret = (char *)malloc(len * sizeof(char));
	//if null...
	int i = 0;
	while(static_str[i])
	{
		str_to_ret[i] = static_str[i];
		i++;
	}
	int k = 0;
	while(buffer[k])
	{
		str_to_ret[i + k] = buffer[k];
		k++;
	}
	str_to_ret[i + k] = '\0';


	return str_to_ret;


}

char *str_to_return(char *static_str)
{
	int i = 0;

	while (static_str[i] != '\n')
		i++;
	char *str_to_ret;

	str_to_ret = (char *)malloc((i + 2) * sizeof(char));
	i = 0;
	while(static_str[i] != '\n')
	{
		str_to_ret[i] = static_str[i];
		i++;
	}
	str_to_ret[i] = static_str[i];
	i++;
	str_to_ret[i] = '\0';

	return str_to_ret;
}

char *str_to_save(char *static_str)
{
	char *str_to_ret;
	int i = 0;

	while (static_str[i] != '\n')
		i++;
	i++;
	int k = 0;
	while (static_str[i + k] != '\0')
	{
		k++;
	}
	str_to_ret = (char *)malloc((k + 1) * sizeof(char));
	k = 0;
	while (static_str[i + k])
	{
		str_to_ret[k] = static_str[i + k];
		k++;
	}
	str_to_ret[k] = '\0';



	return str_to_ret;

}



char *get_next_line(int fd)
{
	static char *static_str;
	char		*joint_str;
	char		*tmp;
	static int	the_end;
	char		*buffer;
	char		*str_to_ret;
	int			read_bytes;

	/*initial checks and setting static and buffer*/	
	if (fd < 0)
		return NULL;
	if (BUFFER_SIZE <= 0)
		return NULL;
	
/////AAAAAthe_end = 1
	if (the_end == 1)
		return NULL;
	if (static_str == NULL)
	{
		static_str = (char *)malloc(1 * sizeof(char));
		//if null...
		static_str[0] = '\0';
	}
	
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	//if null...
//	buffer[BUFFER_SIZE] = '\0';
	/*read for nl filling the buffer*/
read_bytes = 1;

while (read_bytes > 0 && ft_strchr(static_str, '\n') == NULL)
{

	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes < 0)
		return(free(buffer), NULL);
	buffer[read_bytes] = '\0';
	joint_str = ft_strjoin(static_str, buffer);
	free(static_str);
	static_str = joint_str;
	
}
free(buffer);

	/*what to save...what to return*/

int i = 0;
while(static_str[i] && static_str[i] != '\n')
	i++;
if (static_str[i] == '\0')
{
	if (i == 0)
	{
		//AAA NON AVEVI FATTO IL FREE DI STATIC
		free(static_str);
		the_end = 1;
		return NULL;
	}
	the_end = 1;
	str_to_ret = static_str;
}
else
{
	tmp = str_to_save(static_str);
	str_to_ret = str_to_return(static_str);
	free(static_str);
	static_str = tmp;

}
//manage the end 
return str_to_ret;

}


/*
int main()
{
	open("./file.txt", O_RDONLY);

}
*/
