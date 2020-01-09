#ifndef FILLIT_H
# define FILLIT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdint.h>
# include "libft/libft.h"

# define MAX_COUNT 26
# define MAX_SIZE_MAP 16

typedef struct	s_figure
{
	uint64_t	value;
	char		word;
	int			x;
	int			y;
	int			width;
	int			height;
}				t_figure;

int				check_and_get_count(int fd, t_figure *figures);
int				find_map(t_figure *figures, int count, uint16_t *map);

#endif
