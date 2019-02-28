/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atep <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:49:51 by atep              #+#    #+#             */
/*   Updated: 2019/02/28 10:32:04 by atep             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_tab	*ft_init_struct(int fd, t_tab **lst)
{
	t_tab	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		if ((tmp = (t_tab*)malloc(sizeof(t_tab))) == NULL)
			return (NULL);
		tmp->fd = fd;
		tmp->str = NULL;
		tmp->next = *lst;
		*lst = tmp;
	}
	return (tmp);
}

int		ft_get_line(char *buff, char **str, char **line)
{
	char	*tmp;

	tmp = *str;
	if ((*str = ft_strjoin(tmp, buff)) == NULL)
	{
		*str = tmp;
		return (-1);
	}
	if (tmp)
		free(tmp);
	if ((tmp = ft_strchr(*str, '\n')) != NULL)
	{
		if ((*line = ft_strsub(*str, 0, tmp - (*str))) == NULL)
			return (-1);
		buff = *str;
		if (tmp[1] && (*str = ft_strdup(tmp + 1)) == NULL)
			return (-1);
		else if (!tmp[1])
			*str = NULL;
		free(buff);
		return (1);
	}
	return (0);
}

int		ft_endoffile(char **str, char **line)
{
	if (!ft_strlen(*str))
	{
		free(*str);
		*str = NULL;
		return (0);
	}
	if (ft_strchr(*str, '\n') != NULL)
		ft_get_line(NULL, str, line);
	else
	{
		if ((*line = ft_strdup(*str)) == NULL)
			return (-1);
		free(*str);
		*str = NULL;
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_tab	*lst = NULL;
	long			i;
	char			buff[BUFF_SIZE + 1];
	t_tab			*tmp;
	
	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!(tmp = ft_init_struct(fd, &lst)))
		return (-1);
	ft_bzero(buff, BUFF_SIZE + 1);
	while ((i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[i] = '\0';
		if ((i = ft_get_line(buff, &tmp->str, line)))
			return ((int)i);
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	if (i == 0 && tmp->str != NULL)
		return (ft_endoffile(&tmp->str, line));	
	return ((i < 0) ? -1 : 0);
}