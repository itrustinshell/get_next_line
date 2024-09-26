
#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
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

char	*ft_strdup(const char *s)
{
	size_t	size_malloc;
	char	*new;
	char	*initial;

	size_malloc = (ft_strlen(s) + 1) * sizeof(char);
	new = malloc(size_malloc);
	if (new == NULL)
		return (NULL);
	else
		initial = new;
	while (*s != '\0')
	{
		*new = *s;
		new++;
		s++;
	}
	*new = '\0';
	new = initial;
	return (new);
}

char	*ft_strndup(const char *s, size_t len)
{
	size_t	size_malloc;
	char	*new;
	char	*initial;
	size_t	i;

	size_malloc = (len + 1) * sizeof(char);
	new = malloc(size_malloc);
	if (new == NULL)
	{
		return (NULL);
	}
	else
		initial = new;
	i = 0;
	while (i < len)
	{
		*new = *s;
		new++;
		s++;
		i++;
	}
	*new = '\0';
	new = initial;
	return (new);
}

size_t	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*



c  i  a  o  \0      c  o  m  e  \0
0  1  2  3  4       0  1  2  3  4

strlen(a) = 4		strlen(b) = 4
len_joint = 8;


c i a o c o m e \0
0 1 2 3 4 5 6 7 8

*/
char	*ft_strjoin(char *initial_string, char *buffer_to_add)
{
	int	i = 0;
	int	j = 0;
	char	*joint_str;
	int joint_len;
/*
	if (initial_string == NULL)
		initial_string = "";
*/
	joint_str = NULL;
    if (initial_string == NULL)
	{
		joint_len = ft_strlen(buffer_to_add) + 1; 
		joint_str = (char *)malloc(joint_len * sizeof(char));
		if (joint_str == NULL)
			return (NULL);
		while (buffer_to_add[i] != '\0')
		{
			joint_str[i] = buffer_to_add[i];
			i++;
		}
		joint_str[i] = '\0';
    	return joint_str;
	}
	if (initial_string != NULL)
	{
		if (initial_string[0] == '\0')
		{	joint_len = ft_strlen(buffer_to_add) + 1; 
		joint_str = (char *)malloc(joint_len * sizeof(char));
		if (joint_str == NULL)
			return (NULL);
		while (buffer_to_add[i] != '\0')
		{
			joint_str[i] = buffer_to_add[i];
			i++;
		}
		joint_str[i] = '\0';
    	return joint_str;
		}

	}
	joint_len = ft_strlen(initial_string) + ft_strlen(buffer_to_add) + 1; 
	joint_str = (char *)malloc(joint_len * sizeof(char));
	if (joint_str == NULL)
		return (NULL);
	i = 0;
	while (initial_string[i] != '\0')
	{
		joint_str[i] = initial_string[i];
		i++;
	}
	while (buffer_to_add[j] != '\0')
	{
		joint_str[i + j] = buffer_to_add[j];
		j++;
	}
	joint_str[i+j] = '\0';
	return ( joint_str);
}
