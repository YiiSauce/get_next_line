/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-ouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 22:09:09 by yait-ouc          #+#    #+#             */
/*   Updated: 2021/12/13 22:18:45 by yait-ouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*readbon(int fd, char *tmp)
{
	int		i;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	i = 1;
	while (!ft_strchr(tmp, '\n') && i)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1 || (tmp[0] == 0 && i == 0))
		{
			free(buf);
			buf = NULL;
			free(tmp);
			tmp = NULL;
			return (NULL);
		}
		buf[i] = '\0';
		tmp = ft_strjoin(tmp, buf);
	}
	free(buf);
	return (tmp);
}

char	*get_linebon(char *t)
{
	int		n;
	char	*line;

	n = 0;
	if (!t)
		return (NULL);
	while (t[n] && t[n] != '\n')
		n++;
	if (t[n] == '\0')
		line = (char *)malloc(n + 1);
	else
		line = (char *)malloc(n + 2);
	if (!line)
		return (NULL);
	n = 0;
	while (t[n] && t[n] != '\n')
	{
		line[n] = t[n];
		n++;
	}
	if (t[n] == '\n')
		line[n++] = '\n';
	line[n] = '\0';
	return (line);
}

char	*restbon(char *tmp)
{
	char	*rst;
	int		k;
	int		i;

	k = 0;
	while (tmp[k] && tmp[k] != '\n')
		k++;
	if (!tmp[k])
	{
		free(tmp);
		return (NULL);
	}
	k++;
	i = ft_strlen(&tmp[k]);
	rst = malloc(i + 1);
	if (!rst)
		return (NULL);
	i = 0;
	while (tmp[k])
		rst[i++] = tmp[k++];
	rst[i] = '\0';
	free(tmp);
	return (rst);
}

char	*get_next_line(int fd)
{
	char		*ln;
	static char	*tp[1024];

	if (BUFFER_SIZE <= 0 || fd < -1)
		return (NULL);
	if (!tp[fd])
		tp[fd] = ft_strdup("");
	tp[fd] = readbon(fd, tp[fd]);
	if (!tp[fd])
		return (NULL);
	ln = get_linebon(tp[fd]);
	tp[fd] = restbon(tp[fd]);
	return (ln);
}
