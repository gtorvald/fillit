#include "fillit.h"

int		find_size(t_figure *figures, int size, uint16_t *map)
{
	if (figures->word == 0)
		return (0);
	figures->y = 0;
	while (figures->y <= size - figures->height)
	{
		figures->x = 0;
		while (figures->x <= size - figures->width)
		{
			if (!(*(uint64_t*)(map + figures->y) & (figures->value >> figures->x)))
			{
				*(uint64_t*)(map + figures->y) |= figures->value >> figures->x;
				if (!find_size(figures + 1, size, map))
					return (0);
				*(uint64_t*)(map + figures->y) ^= figures->value >> figures->x;
			}
			figures->x++;
		}
		figures->y++;
	}
	figures->x = 0;
	figures->y = 0;
	return (1);
}

int		find_map(t_figure *figures, int count, uint16_t *map)
{
	int		size;

	size = 2;
	while (size * size < count * 4)
		size++;
	while (find_size(figures, size, map) && size < 17)
	{
		ft_bzero(map, sizeof(uint16_t) * MAX_SIZE_MAP);
		size++;
	}
	if (size == 17)
		return (0);
	return (size);
}
