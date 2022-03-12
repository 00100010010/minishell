/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_linux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:20:02 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/25 10:23:39 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_line(char **stock, int fd)
{
	int	i;

	i = 0;
	while (stock[fd][i] != '\n' && stock[fd][i])
		i++;
	if (stock[fd][i] == '\n')
		return (1);
	return (0);
}

int	ft_move_to_stock(char **stock, char *buffer, int fd)
{
	char	*stock_tmp;

	if (!stock[fd])
		stock[fd] = ft_strdup("");
	stock_tmp = stock[fd];
	stock[fd] = ft_strjoin(stock_tmp, buffer);
	if (!stock[fd])
		return (-1);
	free(stock_tmp);
	if (ft_check_line(stock, fd))
		return (1);
	return (0);
}

int	ft_cleanstock_makeline(char **stock, char **line, int fd)
{
	char	*stock_tmp;
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(stock[fd]);
	while (stock[fd][i] != '\n' && stock[fd][i])
		i++;
	*line = ft_substr((const char *)stock[fd], 0, i);
	if (!*line)
		return (-1);
	stock_tmp = ft_substr(stock[fd], i + 1, len - i - 1);
	if (!stock_tmp)
		return (-1);
	free(stock[fd]);
	stock[fd] = stock_tmp;
	return (1);
}

int	ft_read(int flag, int fd, char **stock, char *buffer)
{
	int	len;

	len = 1;
	while (!flag && len)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		buffer[len] = '\0';
		flag = ft_move_to_stock(stock, buffer, fd);
		if (flag == -1)
			return (-1);
	}
	return (len);
}

int	get_next_line(int fd, char **line)
{
	static char	*stock[FOPEN_MAX + 1];
	char		*buffer;
	int			flag;
	int			len;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line || BUFFER_SIZE < 1 || fd < 0 || fd > FOPEN_MAX || buffer == NULL
		|| read(fd, buffer, 0) < 0 || BUFFER_SIZE > 2147483647)
	{
		if (line && BUFFER_SIZE >= 1 && fd >= 0 && fd <= FOPEN_MAX)
			free(buffer);
		return (-1);
	}
	flag = 0;
	if (stock[fd])
		flag = ft_check_line(stock, fd);
	len = ft_read(flag, fd, stock, buffer);
	free(buffer);
	if (len == -1 || (ft_cleanstock_makeline(stock, line, fd)) == -1)
		return (-1);
	if (len > 0)
		return (1);
	free(stock[fd]);
	stock[fd] = NULL;
	return (0);
}
