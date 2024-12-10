/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:07:56 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/15 14:25:35 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_next_line(int fd, char *buffer)
{
	ssize_t	btsread;
	char	*nextbuild;

	btsread = 0;
	nextbuild = (char *)malloc(ft_strlen(buffer) + 1);
	if (!nextbuild)
		return (NULL);
	ft_memcpy(nextbuild, buffer, ft_strlen(buffer) + 1);
	while (!ft_strchr(nextbuild, '\n'))
	{
		btsread = read(fd, buffer, BUFFER_SIZE);
		if (btsread == 0)
			return (nextbuild);
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
	static char	buffer[BUFFER_SIZE + 1];
	char		*nextline;

	if ((fd < 0 || fd > OPEN_MAX) || (read(fd, buffer, 0) < 0))
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		return (NULL);
	}
	nextline = read_next_line(fd, buffer);
	if (nextline == NULL)
		return (NULL);
	if (*nextline == '\0')
		return (free(nextline), NULL);
	nextline = ft_cutstr(nextline);
	ft_rearange_buffer(buffer);
	return (nextline);
}

int	main(void)
{
	int		i;
	int		x;
	int		fd;
	char	*str;

	i = 0;
	x = 5;
	fd = open("test.txt", O_RDONLY);
	while (i++ <= x)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
	}
	close (fd);
}

