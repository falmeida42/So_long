/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:51:08 by gumatos           #+#    #+#             */
/*   Updated: 2021/08/18 14:52:39 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	ft_find_char(char *str, char c)
{
	int		i;

	i = -1;
	while (*(str + ++i))
		if (*(str + i) == c)
			return (i);
	return (-1);
}

void	free_buff(char **buff)
{
	free(*buff);
	*buff = NULL;
}

int	ft_add_line(char **buff, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*buff)[i] != '\n' && (*buff)[i] != '\0')
		++i;
	if ((*buff)[i] == '\n')
	{
		(*line) = ft_substr(*buff, 0, i);
		tmp = ft_strdup(&((*buff)[i + 1]));
		if (!(*line) || !(tmp))
			return (-1);
		free(*buff);
		*buff = tmp;
		if (**buff == '\0')
			free_buff(buff);
		return (1);
	}
	else
	{
		if (else_add_line(line, buff) == -1)
			return (-1);
		return (0);
	}
}

int	ft_out(char **buff, char **line, char **buff_read, int ret)
{
	free(*buff_read);
	if (ret < 0)
		return (-1);
	else if (ret == 0 && *buff == NULL)
	{
		(*line) = ft_strdup("");
		if (!(*line))
			return (-1);
		return (0);
	}
	else
		return (ft_add_line(buff, line));
}

int	get_next_line(int fd, char **line)
{
	static char	*buff = NULL;
	char		*buff_read;
	char		*tmp;
	int			ret;

	buff_read = malloc(sizeof(*buff_read) * (BUFFER_SIZE + 1));
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0
		|| !(buff_read))
		return (-1);
	ret = read(fd, buff_read, BUFFER_SIZE);
	while (ret > 0)
	{
		buff_read[ret] = '\0';
		if (buff == NULL)
			buff = ft_strdup(buff_read);
		else
			buff = else_gnl(buff, buff_read);
		if (!buff)
			return (-1);
		if (ft_find_char(buff, '\n') != -1)
			break ;
		ret = read(fd, buff_read, BUFFER_SIZE);
	}
	return (ft_out(&buff, line, &buff_read, ret));
}
