#include "ft_malcolm.h"

void	cpmac(uint8_t *dst, uint8_t src[6])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		dst[i] = src[i];
		i++;
	}
}
