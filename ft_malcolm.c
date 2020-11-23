#include "ft_malcolm.h"

int	end(char *s, int ret)
{
	printf("%s", s);
	perror(NULL);
	if (errno)
		printf("errno : %d\n", errno);
	return (ret);

}

uint8_t		*get_mac()
{
	struct ifaddrs		*addr = NULL, *ptr = NULL;
	struct sockaddr_ll	*ll;
	uint8_t			*ret;

	if (getifaddrs(&addr) < 0)
		perror("getifaddrs");
	else
	{
		ptr = addr;
		while (ptr)
		{
			if (ptr->ifa_addr && ptr->ifa_addr->sa_family == AF_PACKET
					&& strcmp("lo", ptr->ifa_name))
			{
				ll = (struct sockaddr_ll *)ptr->ifa_addr;
				ret = NULL;	
				if ((ret = malloc(sizeof(uint8_t) * ll->sll_halen)))
					ret = memcpy(ret, (uint8_t *)ll->sll_addr, ll->sll_halen);
				freeifaddrs(addr);
				return (ret);
			}
			ptr = ptr->ifa_next;
		}
		freeifaddrs(addr);
	}
	return (NULL);
}

void	setup_packet(int sock, t_args *args, t_arp *packet)
{
	packet->protocol = AR_PROTOCOL;
	packet->hln = 6;
	packet->pln = 4;
	packet->op = REPLY;
}

int	main(int ac, char **av)
{
	int 			sock;
	t_args			args;
	t_arp			packet;
	uint8_t			*mac;

	if (parse_args(ac, av, &args) < 0)
		return (end("bad arguments.\n", -1));
	if (!(sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))))
		return (end("socket fucked.\n", -1));
	if ((mac = get_mac()) == NULL)
	{
		close(sock);
		return (end("get_mac error.\n", -1));
	}
	int i = 0;
	while (mac[i])
	{
		printf("%d:", mac[i]);
		i++;
	}
	printf("\n");
	setup_packet(sock, &args, &packet);
	close(sock);
	printf("everything went well.\n");
	return (0);

}
