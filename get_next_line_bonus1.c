/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:11:03 by pstrohal          #+#    #+#             */
/*   Updated: 2024/04/06 15:51:04 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus1.h"

char	*read_next_line(int fd, char *buffer, char **strbuff)
{
	ssize_t	btsread;
	char	*nextbuild;

	btsread = 0;
	nextbuild = (char *)malloc(ft_strlen(buffer) + 1);
	if (!nextbuild)
		return (NULL);
	ft_memcpy(nextbuild, *strbuff, ft_strlen(*strbuff) + 1);
	while (!ft_strchr(nextbuild, '\n'))
	{
		btsread = read(fd, buffer, BUFFER_SIZE);
		if (btsread == 0)
		{
			free(*strbuff);
			return (*strbuff = NULL, nextbuild);
		}
		else if (btsread == -1)
			return (free(nextbuild), NULL);
		else
			buffer[btsread] = '\0';
		nextbuild = ft_strjoin(nextbuild, buffer);
		if (!nextbuild)
			return (NULL);
	}
	return (nextbuild);
}

char	*ft_cutstr(char *nextline)
{
	int		i;
	char	*cutstring;

	cutstring = ft_strchr(nextline, '\n');
	if (!cutstring)
	{
		i = ft_strlen(nextline);
		i--;
	}
	else
		i = cutstring - nextline;
	cutstring = (char *)malloc((i + 2) * sizeof(char));
	if (!cutstring)
		return (free(nextline), NULL);
	ft_memcpy(cutstring, nextline, i + 1);
	free(nextline);
	cutstring[i + 1] = '\0';
	return (cutstring);
}

void	ft_rearange_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\n')
	{
		if (buffer[i++] == '\0')
		{
			buffer[0] = '\0';
			return ;
		}
	}
	ft_memcpy(buffer, &buffer[i + 1], BUFFER_SIZE - i);
}

char	*get_next_line(int fd)
{
	static char	*strbuff[OPEN_MAX];
	char		buffer[BUFFER_SIZE + 1];
	char		*nextline;

	if ((fd < 0 || fd > OPEN_MAX) || (read(fd, buffer, 0) < 0))
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		return (NULL);
	}
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (!strbuff[fd])
		strbuff[fd] = (char *)malloc(BUFFER_SIZE + 1);
	if (!strbuff[fd])
		return (NULL);
	nextline = read_next_line(fd, buffer, &strbuff[fd]);
	if (nextline == NULL)
		return (free (strbuff[fd]), NULL);
	if (!strbuff[fd] && *nextline == '\0')
		return (free(nextline), NULL);
	nextline = ft_cutstr(nextline);
	ft_rearange_buffer(buffer);
	if (strbuff[fd])
		ft_memcpy(strbuff[fd], buffer, ft_strlen(buffer) + 1);
	return (nextline);
}

// int	main(void)
// {
// 	int		i;
// 	int		x;
// 	int		fd[4];
// 	char	*str;

// 	i = 1;
// 	x = 0;
// 	fd[0] = open("empty", O_RDONLY);
// 	// fd[1] = open("test2.txt", O_RDONLY);
// 	// fd[2] = open("test3.txt", O_RDONLY);
// 	// fd[3] = open("test4.txt", O_RDONLY);
// 	while (i-- >= 0)
// 	{
// 		// printf("test %d$\n", (x + 1));
// 		str = get_next_line(fd[x]);
// 		printf("%s$\n", str);
// 		// if (x == 3)
// 		// {
// 		// 	x = 0;
// 		// 	printf("------------------------------------------------\n");
// 		// }
// 		// else
// 		// 	x++;
// 	}
// 	close (fd[0]);
// 	// close (fd[1]);
// 	// close (fd[2]);
// 	// close (fd[3]);
// 	free(str);
// }
