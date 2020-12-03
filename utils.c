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

void	wait_packet(int sock, t_arp *request)
{
	int lenght = 0;
	while (lenght == 0)
	{
		lenght = recvfrom(sock, (void *)request, sizeof(request), 0, NULL, NULL);
		printf("fd %d\n", sock);
	}
	if (lenght == -1)
		perror("recvfrom()");
	else
		printf("MAC %d %d %d %d %d %d\n", request->sha[0], request->sha[1], request->sha[2], request->sha[3], request->sha[4], request->sha[5]);
}
