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
	struct ifaddrs *ifr;
	packet->protocol = AR_PROTOCOL;
	packet->hln = 6;
	packet->pln = 4;
	packet->op = REPLY;
	memset(&ifr, 0, sizeof(ifr));
	getifaddrs(&ifr);
	//ioctl(sock, SIOCGIFHWADDR, ifr);
	perror("perror");
	int i = 0;
	while (i <= 14)
	{
		printf("%c ", ifr->ifa_addr->sa_data[i]);
		i++;
	}
	freeifaddrs(ifr);
}

int	main(int ac, char **av)
{
	int 	sock;
	t_args	args;
	t_arp	packet;

	if (parse_args(ac, av, &args) < 0)
		return (end("bad arguments.\n", -1));
	if (!(sock = socket(AF_INET, SOCK_RAW, htons(ETH_P_ARP))))
		return (end("socket fucked.\n", -1));
	setup_packet(sock, &args, &packet);
	close(sock);
	printf("everything went well.\n");
	return (0);

}
