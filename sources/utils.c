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

int wait_packet(int sock)
{
	ssize_t	lenght = 0;
	t_arp	request;
	while (!(lenght = recvfrom(sock, &request, sizeof(request), 0, NULL, NULL)))
		if (lenght == -1)
			return (lenght);
	printf("MAC %d %d %d %d %d %d\n", request.sha[0], request.sha[1], request.sha[2], request.sha[3], request.sha[4], request.sha[5]);
	return (0);
}
