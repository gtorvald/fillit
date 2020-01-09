# include <unistd.h>
#include "fillit.h"

void		get_min_and_max_xy(int *minmax, char *str)
{
	int		i;

	minmax[0] = 3;
	minmax[1] = 0;
	minmax[2] = 3;
	minmax[3] = 0;
	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if (i % 5 < minmax[0])
				minmax[0] = i % 5;
			if (i % 5 > minmax[1])
				minmax[1] = i % 5;
			if (i / 5 < minmax[2])
				minmax[2] = i / 5;
			if (i / 5 > minmax[3])
				minmax[3] = i / 5;
		}
		i++;
	}
}

t_figure	to_struct(char *str, char word)
{
	int			minmax[4];
	t_figure	figure;
	int			i;
	int			j;

	figure.value = 0;
	get_min_and_max_xy(minmax, str);
	figure.width = minmax[1] - minmax[0] + 1;
	figure.height = minmax[3] - minmax[2] + 1;
	figure.word = word;
	i = 0;
	while (i < figure.width)
	{
		j = 0;
		while (j < figure.height)
		{
			if (str[minmax[0] + i + (minmax[2] + j) * 5] == '#')
				figure.value |= (1L << (16 * (j + 1) - i - 1));
			j++;
		}
		i++;
	}
	return (figure);
}

int			check_connections(char *str)
{
	int		i;
	int		connections;

	connections = 0;
	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if (i - 1 >= 0 && str[i - 1] == '#')
				connections++;
			if (i + 1 < 20 && str[i + 1] == '#')
				connections++;
			if (i - 5 >= 0 && str[i - 5] == '#')
				connections++;
			if (i + 5 < 20 && str[i + 5] == '#')
				connections++;
		}
		i++;
	}
	if (connections == 6 || connections == 8)
		return (0);
	return (1);
}

int			check_symbols(char *str)
{
	int		i;
	int		parts;

	i = 0;
	parts = 0;
	while (i < 20)
	{
		if (i % 5 == 4 && str[i] != '\n')
			return (1);
		if (i % 5 != 4 && str[i] != '.' && str[i] != '#')
			return (1);
		if (str[i] == '#' && ++parts > 4)
			return (1);
		i++;
	}
	if (check_connections(str))
		return (1);
	return (0);
}

int			check_and_get_count(int fd, t_figure *figures)
{
	int		i;
	char	buf[21];
	char	word;
	int		symbols;

	word = 'A';
	i = 0;
	while (1)
	{
		if (i != 0)
			read(fd, buf, 1);
		if ((symbols = read(fd, buf, 20)) != 20)
			break ;
		if (check_symbols(buf) || word == 'Z' + 2)
		{
			close(fd);
			return (0);
		}
		figures[i] = to_struct(buf, word++);
		i++;
	}
	close(fd);
	if (symbols != 0 || buf[0] == '\n')
		return (0);
	return (word - 'A');
}
