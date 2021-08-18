/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:45:48 by gumatos           #+#    #+#             */
/*   Updated: 2021/08/18 14:52:51 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	else_add_line(char **line, char **buff)
{
	(*line) = ft_strdup(*buff);
	if (!(*line))
		return (-1);
	free_buff(buff);
	return (0);
}

char	*else_gnl(char *buff, char *buff_read)
{
	char	*tmp;

	tmp = ft_strjoin(buff, buff_read);
	free(buff);
	return (tmp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		len_s1;
	int		len_s2;
	int		i;

	len_s1 = 0;
	while (*(s1 + len_s1))
		++len_s1;
	len_s2 = 0;
	while (*(s2 + len_s2))
		++len_s2;
	tmp = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!(tmp))
		return (NULL);
	i = -1;
	while (++i < len_s1)
		tmp[i] = s1[i];
	i = -1;
	while (++i < len_s2)
		tmp[len_s1 + i] = s2[i];
	tmp[len_s1 + len_s2] = '\0';
	return (tmp);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	size;

	size = 0;
	while (*(s + size))
		++size;
	if (start > size)
	{
		tmp = malloc(sizeof(*tmp));
		if (!(tmp))
			return (0);
		*tmp = '\0';
		return (tmp);
	}
	tmp = malloc(sizeof(*tmp) * (len + 1));
	if (!s || !(tmp))
		return (0);
	*(tmp + len) = 0;
	while (len--)
		*(tmp + len) = *(s + start + len);
	return (tmp);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*tmp;

	i = 0;
	while (*(s1 + i))
		++i;
	tmp = malloc(sizeof(*tmp) * (i + 1));
	if (!(tmp))
		return (NULL);
	i = -1;
	while (*(s1 + ++i))
		*(tmp + i) = *(s1 + i);
	*(tmp + i) = '\0';
	return (tmp);
}
