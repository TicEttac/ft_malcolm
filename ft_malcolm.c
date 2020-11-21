#include "ft_malcolm.h"

int	end(char *s, int ret)
{
	printf("%s", s);
	perror(NULL);
	if (errno)
		printf("errno : %d\n", errno);
	return (ret);

}

void	setup_packet(int sock, t_args *args, t_arp *packet)
{
	t_io	arp;
	unsigned char	*a;

	packet->protocol = AR_PROTOCOL;
	packet->hln = 6;
	packet->pln = 4;
	packet->op = REPLY;
	memset(&arp, 0, sizeof(arp));
	a = &arp.ha.sa_data[0];
	ioctl(sock, SIOCGARP, &arp);
	perror("perror");
	int i = 0;
	while (i <= 5)
	{
		printf("%d:", a[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	int 	sock;
	t_args	args;
	t_arp	packet;

	if (parse_args(ac, av, &args) < 0)
		return (end("bad arguments.\n", -1));
	if (!(sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))))
		return (end("socket fucked.\n", -1));
	setup_packet(sock, &args, &packet);
	close(sock);
	printf("everything went well.\n");
	return (0);

}
