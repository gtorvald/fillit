#include <stdlib.h>
#include "fillit.h"

char	*get_clean_map(int size)
{
	int		i;
	char	*str;
	int		size_str;

	size_str = size * (size + 1);
	str = malloc(sizeof(char) * size_str);
	str[size_str] = '\0';
	i = 0;
	while (i < size_str)
	{
		if (i % (size + 1) == size)
			str[i] = '\n';
		else
			str[i] = '.';
		i++;
	}
	return (str);
}

void	print_result(t_figure *fig, int size)
{
	char	*str;
	int		i;
	int		j;

	str = get_clean_map(size);
	while (fig->word != 0)
	{
		i = 0;
		while (i < fig->width)
		{
			j = 0;
			while (j < fig->height)
			{
				if ((fig->value >> (16 * (j + 1) - i - 1)) & 1L)
					str[(fig->y + j) * (size + 1) + fig->x + i] = fig->word;
				j++;
			}
			i++;
		}
		fig++;
	}
	ft_putstr(str);
	free(str);
}


int		print_error_message(char *str)
{
	ft_putstr(str);
	return (1);
}

int		main(int argc, char **argv)
{
	t_figure	figures[MAX_COUNT + 1];
	uint16_t	map[MAX_SIZE_MAP];
	int			count;
	int			size;
	int			fd;

	if (argc != 2)
		return (print_error_message("usage: ./fillit [filename]\n"));
	ft_bzero(figures, sizeof(t_figure) * (MAX_COUNT + 1));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (print_error_message("error\n"));
	if ((count = check_and_get_count(fd, figures)) < 1 || count > MAX_COUNT)
		return (print_error_message("error\n"));
	ft_bzero(map, sizeof(uint16_t) * MAX_SIZE_MAP);
	if ((size = find_map(figures, count, map)) == 0)
		return (print_error_message("error\n"));
	print_result(figures, size);
	return (0);
}
