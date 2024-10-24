#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

/*
se esiste leggi fino a n1
 leggi il buffer fino a \n
se trovi \n 

se esiste nl ritorna quella stringa fino a nl

se n> 0 esiste e non ha ancora nl fai uno stjoin

//if \nl 

return fino a nl
return la stringa per essere lavorata



*/
	
int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return i;
}
	
void ft_strcpy(char *buffer, char *ret)
{
	int i;
	i = 0;

	while (buffer[i])
	{
		ret[i] = buffer[i];
		i++;
	}
	ret[i] = '\0';
}

void ft_strcpy_two(char *savedstr, char *buffer, char *ret)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (savedstr[i])
	{
		ret[i] = savedstr[i];
		i++;
	}
	while (buffer[j])
	{
		ret[i + j] = buffer[j];
		j++;
	}
	ret[i + j] = '\0';

}

char *ft_strjoin(char *savedstr, char *buffer)
{	
	char	*ret;
	int len;

	if (savedstr == NULL)
		len = 0 + ft_strlen(buffer);
	else
		len = ft_strlen(savedstr) + ft_strlen(buffer);
	ret = (char *)malloc((len + 1) * sizeof(char));

	if (savedstr == NULL)
		ft_strcpy(buffer, ret);
	else
		ft_strcpy_two(savedstr, buffer, ret);
	
	return (ret);
	
}	
	
int there_is_nl(char *str)
{
	int i;

	if (str == NULL)
		return 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}


char *get_next_line(int fd)
{
		int		n;
		char	*buffer;
		static char	*savedstr;

		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer == NULL)
		{
			printf("error: buffer is NULL\n");
			return NULL;
		}
		buffer[BUFFER_SIZE] = '\0';
		n = 1;
		while(n > 0 && !there_is_nl(savedstr))
		{
			
			printf("wewewew\n");
			n = read(fd, buffer, BUFFER_SIZE);
			if (n < 0)
			{
				printf("error: n = %d\n", n);
				free(buffer);
				return (NULL);
			}
			printf("n: %d\n", n);

			savedstr = ft_strjoin(savedstr, buffer);

		}
		return savedstr;	
}



int main(void)
{
	char *path;
	char *str;

	path = "./file.txt";
	int fd = open(path, O_RDONLY);

	str = get_next_line(fd);

	if (str)
		printf("%s\n", str);
	





}
