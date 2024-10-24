
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

int	ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


char	*ft_strjoin(char *initial_string, char *buffer_to_add)
{
	int		i;
	int		j;
	char	*joint_str;
	int 	joint_len;
	
 	if (initial_string == NULL || buffer_to_add == NULL)
		return (NULL);
			
	joint_str = NULL;	
	joint_len = ft_strlen(initial_string) + ft_strlen(buffer_to_add) + 1; 
	
	joint_str = (char *)malloc(joint_len * sizeof(char));
	if (joint_str == NULL)
		return (NULL);
	
	i = -1;
	while (initial_string[++i] != '\0')
		joint_str[i] = initial_string[i];
		
	j = -1;
	while (buffer_to_add[++j] != '\0')
		joint_str[i + j] = buffer_to_add[j];	
	joint_str[i + j] = '\0';

	return (joint_str);
}
