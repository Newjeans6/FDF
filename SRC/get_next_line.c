/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:47:55 by aviscogl          #+#    #+#             */
/*   Updated: 2024/12/06 09:05:06 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)s;
	while (i < n)
	{
		temp[i] = '\0';
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	str[BUFFER_SIZE + 1] = {0};
	int			index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	index = 1;
	line = ft_strdup(str);
	if (!line)
		return (NULL);
	while (index > 0 && !ft_strchr(line, '\n'))
	{
		index = read(fd, str, BUFFER_SIZE);
		if (index == -1)
			return (ft_bzero(str, BUFFER_SIZE), free(line), NULL);
		str[index] = '\0';
		line = ft_strjoin(line, str);
		if (!line)
			return (NULL);
	}
	if (index == 0 && !line[0])
		return (free(line), NULL);
	ft_update(str);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("fichier.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
