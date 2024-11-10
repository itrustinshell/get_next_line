#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *staticstr, char *buffer)
{
	int		len;
	int		i;
	int		j;
	char	*ret;

	len = ft_strlen(staticstr) + ft_strlen(buffer);
	ret = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	while (staticstr[i])
	{
		ret[i] = staticstr[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		ret[i + j] = buffer[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c )
	{
		i++;
	}
	if (s[i] == c)
	{
		return (1);
	}
	return (0);
}

char *extract_ret(char *staticstr)
{
	int		i;
	char	*ret;

	i = 0;
	while (staticstr[i] && staticstr[i] != '\n')
		i++;
	ret = (char *)malloc((i + 2) * sizeof(char));
	i = 0;
	while (staticstr[i] != '\n')
	{
		ret[i] = staticstr[i];
		i++;
	}
	ret[i] = staticstr[i];
	i++;
	ret[i] = '\0';
	return (ret);
}

char	*update_static(char *staticstr)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (staticstr[i] && staticstr[i] != '\n')
		i++;
	i++;
	j = 0;
	while (staticstr[i + j])
		j++;
	ret = (char *)malloc((j + 1) * sizeof(char));
	j = 0;
	while (staticstr[i + j])
	{
		ret[j] = staticstr[i + j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}


char	*get_next_line(int fd)
{
	static char	*staticstr;
	char		*tmp;
	char		*ret;
	char		*buffer;
	int			n;

	//initial control
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	//if staticstr is NULL then malloc as follow
	if (!staticstr)
	{
		staticstr = (char *)malloc(sizeof(char));
		if (!staticstr)
			return (NULL);
		staticstr[0] = '\0';
	}

	//building static
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(staticstr);
		return (NULL);
	}
	while (1)
	{
		if (ft_strchr(staticstr, '\n'))
		{
			break;
		}
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (n == 0)
		{
			break;
		}
		buffer[n] = '\0';
		tmp = ft_strjoin(staticstr, buffer);
		free(staticstr);
		staticstr = tmp;
	}
	free(buffer);
	
	// final managment
	if (staticstr[0] == '\0')
	{
		free(staticstr);
		staticstr = NULL;
		return (NULL);
	}
	if (ft_strchr(staticstr, '\n'))
	{
		ret = extract_ret(staticstr);
		tmp = update_static(staticstr);
		free(staticstr);
		staticstr = tmp;
	}
	else
	{
		ret = staticstr;
		staticstr = NULL;
	}	
	return (ret);
}

/*
//create a file named file.txt and write something in it to test.
int main()
{
	char *path = "./file.txt";

	int fd = open(path, O_RDONLY);
	char *ret = get_next_line(fd);

	printf("%s", ret);
}
*/
