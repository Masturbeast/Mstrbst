/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-kar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 14:25:26 by soel-kar          #+#    #+#             */
/*   Updated: 2019/01/07 13:12:55 by soel-kar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					errors(int fd, char **line)
{
	if (fd < 0)
		return (-1);
	if (line == NULL)
		return (-1);
	return (0);
}

int					get_line(int fd, int ret, char **line, char **str)
{
	int				size;
	char			*curr_line;

	size = 0;
	while (str[fd][size] != '\n' && str[fd][size] != '\0')
		size++;
	if (str[fd][size] == '\n')
	{
		*line = ft_strsub(str[fd], 0, size);
		curr_line = ft_strdup(str[fd] + size + 1);
		free(str[fd]);
		str[fd] = curr_line;
		if (str[fd][0] == '\0')
			ft_strdel(&str[fd]);
	}
	else if (str[fd][size] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static char		*str[255];
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*tmp_line;

	if (errors(fd, line) == -1)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strnew(0);
		tmp_line = ft_strjoin(str[fd], buf);
		free(str[fd]);
		str[fd] = tmp_line;
	}
	if (ret < 0)
		return (-1);
	if (ret == 0 && (str[fd] == NULL || str[fd] == '\0'))
		return (0);
	return (get_line(fd, ret, line, str));
}
