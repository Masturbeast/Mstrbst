/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atep <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:49:51 by atep              #+#    #+#             */
/*   Updated: 2019/02/26 16:10:29 by atep             ###   ########.fr       */
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

char	*ft_strdupcat(char *str, char **line)
{
	char	*tmp;
	int		size;

	size = ft_strlen(str) - ft_strlen(ft_strchr(str, '\n'));
	line[0] = ft_strsub(str, 0, size);
	tmp = ft_strsub(str, size + 1, ft_strlen(str));
	free(str);
	if (ft_strlen(tmp) != 0)
		str = ft_strdup(tmp);
	else
		str = NULL;
	free(tmp);
	return (str);
}

char	*ft_catfrombuff(char *buff, char *str, char **line)
{
	char	*tmp;

	if (str == NULL)
		str = ft_strdup(buff);
	else
	{
		tmp = ft_strdup(str);
		free(str);
		str = ft_strjoin(tmp, buff);
		free(tmp);
	}
	if (ft_strchr(str, '\n') != NULL)
		str = ft_strdupcat(str, &line[0]);
	else
		line[0] = NULL;
	return (str);
}

char	*ft_endofline(char *str, char **line)
{
	if (str != NULL)
	{
		if (ft_strchr(str, '\n') != NULL)
			str = ft_strdupcat(str, &line[0]);
		else if (str != NULL)
		{
			line[0] = ft_strdup(str);
			free(str);
			str = NULL;
		}
		else
			line[0] = NULL;
	}
	else
		line[0] = NULL;
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	static t_tab	*lst;
	int				i;
	char			buff[BUFF_SIZE + 1];
	t_tab			*tmp;
	
//	printf("0\n");
	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
//	printf("1\n");
	tmp = ft_init_struct(fd, &lst);
//	printf("2\n");
	while ((i = read(fd, buff, BUFF_SIZE)) > 0)
	{
//		printf("3\n");
		buff[i] = '\0';
//		printf("4\n");
		tmp->str = ft_catfrombuff(buff, tmp->str, &line[0]);
		if(line[0] != NULL)
			return (1);
//		printf("5\n");
//		printf("6\n");
	}
//	printf("7\n");
	if (i == -1)
		return (i);
	tmp->str = ft_endofline(tmp->str, &line[0]);
//	printf("8\n");
	//printf("line[0] = %s\n", line[0]);
	if (line[0] != NULL)
		return (1);
//	printf("9\n");
	return (0);
}
