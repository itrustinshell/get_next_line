#include "get_next_line.h"

/*se entri in questa funzione sai per certo che c'è un nl
 quindi sono eliminati una serie di controlli specifici
 questa funzione estrare da una stringa, la sottostringa che termina con \n.
 aggiunge un null terminator dopo il \n*/
char *nl_strdup(char *str_to_dup)
{
	int i;
	char *str_to_ret;

	i = 0;
	while (str_to_dup[i] != '\n')
		i++;
	str_to_ret = (char *)malloc((i + 2) * sizeof(char));
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

/*se entri qui sai che c'è un \n*/
char *str_to_save(char *str_to_inspect)
{
	int i;
	int k;
	char *str_to_ret;

	i = 0;
	while (str_to_inspect[i] != '\n')
		i++;
	i++; //supero il \n
	k = 0;
	while (str_to_inspect[i + k] != '\0')
		k++;
	str_to_ret = (char *)malloc((k + 1) * sizeof(char));
	k = 0;
	while (str_to_inspect[i + k] != '\0')
	{
		str_to_ret[k] = str_to_inspect[i + k];
		k++;
	}
	str_to_ret[k] = '\0';
	return (str_to_ret);
}


char	*get_next_line(int fd)
{
	static char	*static_str;
	char		*line_to_return;
	char		*tmp;
	static int	the_end;
	/*---reading---*/
	int 		read_bytes;
	char 		*buffer;
	/*------*/
	char	*joint_str_to_copy_in_static;
	int 	i;


/*-----checks and inizialize-----*/
	/*---first check ---*/
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (the_end == 1)
		return (NULL);
	if (static_str == NULL) //at beginning saved_str is always NULL
	{
		static_str = (char *)malloc(1 * sizeof(char));
		static_str[0] = '\0';
	}	
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
/*-------reading---------*/
	read_bytes = 1; //to consent to start while loop
	while (read_bytes > 0 && ft_strchr(static_str, '\n') == NULL)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE); /*fill buffer*/
		if (read_bytes < 0) //error
			return(free(buffer), NULL);
		buffer[read_bytes] = '\0'; //close the buffer	
		joint_str_to_copy_in_static = ft_strjoin(static_str, buffer); //join new_string	
		free(static_str);
		static_str = joint_str_to_copy_in_static;
	}
	free(buffer); 
/*PART TWO what to return */
	i = 0;
	while (static_str[i] != '\0' && static_str[i] != '\n')
		i++;
	if (static_str[i] == '\0') //significa che siamo alla fine non ci ono \n e stampiamo la rimanenza di static str
	{
		if (i == 0) //significa che siamo alla fine e non dobbiamo neanche stampare nnt
		{
			free(static_str);
			static_str = NULL;
			the_end = 1;
			return NULL;
		}
		line_to_return =  static_str;
		the_end = 1;
	}
	else
	{
		line_to_return = nl_strdup(static_str);	//costruisci la stringa da restituire
		tmp = str_to_save(static_str);			// costruisci la stringa da salvare
		free(static_str);
		static_str = NULL;
		static_str = tmp;
	}
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
