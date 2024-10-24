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

/*
se non c'e'un nl continua a leggere finche' puo', aggiungendo di volta in volta le letture a quelle precedenti.

E'importante ricordare che il buffer di lettura va chiuso con il null terminator dopo i tot caratteri letti.

AAA:
se la saved ha gia'un nl ?
ebbene viene ritornata quella saved per poi essere elaborata nell-apposita funzione
*/
char *addbuffer_to_savedstr_until_nl_or_eof(int fd, char *savedstr)
{
	char	*buffer;
	int n;

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
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
		{
			printf("error: n = %d\n", n);
			free(buffer);
			return (NULL);
		}
		buffer[n] = '\0';
		savedstr = ft_strjoin(savedstr, buffer);
	}
	return savedstr;	
}

/*
questa funzione ritorna una stringa fino a l null terminato a meno che non vi sia un nl.
in quel caso ritorna un astringa fino al nl
AAA: bisogna gestire quelche caso speciale ?
*/
char *extract_returnstr_from_savedstr(char *savedstr)
{
	int i;
	char *ret;	

	i = 0;
	
	while (savedstr[i] && savedstr[i] != '\n')
		i++;
	
	ret = (char *)malloc(i * sizeof(char));
	
	i = 0;
	while (savedstr[i] && savedstr[i] != '\n')
	{
		ret[i] = savedstr[i];
		i++;
	}
	ret[i] = '\0';
//	printf("%s\n", ret);
	return (ret);
}

char *delete_extractedstr_from_savedstr(char *savedstr)
{
	int i;
	int j;
	char *ret;
	i = 0;
	while (savedstr[i] && savedstr[i] != '\n')
		i++;
	if (savedstr[i] == '\0')
	{
		free(savedstr);
		savedstr = (char *)malloc(sizeof(char));
		savedstr[0] = '\0';
	}
	else
	{
		i++; //mi porto dopo li nl
		while (savedstr[i + j])
			j++;
		ret =  (char *)malloc(j * sizeof(char));
		j =0;
		while (savedstr[i + j])
		{
			ret[j] = savedstr[i + j];
			j++;
		}
		ret[j] = '\0';
	}
//	printf("%s\n", ret);
	return (ret);
}

char *get_next_line(int fd)
{
	int	n;
	char	*buffer;
	static char	*savedstr;
	int i;
	char *returnstr;

//	if (savedstr != NULL)
//		printf("tx: %s\n",savedstr);
	savedstr = addbuffer_to_savedstr_until_nl_or_eof(fd, savedstr);
//	printf("GG: %s..\n", savedstr);
	returnstr = extract_returnstr_from_savedstr(savedstr);
//	printf("r: %s\n", returnstr);
	savedstr = delete_extractedstr_from_savedstr(savedstr);
//	printf("s: %s\n", savedstr);
	return returnstr;
}



int main(void)
{
	char *path;
	char *str;

	path = "./file.txt";
	int fd = open(path, O_RDONLY);

	str = get_next_line(fd);
//	if (str)
	//	printf("%s\n", str);
	str = get_next_line(fd);
	
	if (str)
		printf("%s\n", str);
	

}
