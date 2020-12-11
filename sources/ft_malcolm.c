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
					ret = memcpy(ret, (uint8_t *)ll->sll_addr,
							sizeof(uint8_t) * ll->sll_halen);
				freeifaddrs(addr);
				return (ret);
			}
			ptr = ptr->ifa_next;
		}
		freeifaddrs(addr);
	}
	return (NULL);
}

void	setup_packet(t_args *args, t_arp *packet)
{
	cpmac(&(packet->dst_mac[0]), args->trg_mac);
	packet->protocol = AR_PROTOCOL;
	packet->hrd = htons(1);//ethernet type
	packet->pro = htons(0x0800);
	packet->hln = 6;
	packet->pln = 4;
	packet->op = REPLY;
	cpmac(&(packet->sha[0]), args->src_mac);
	packet->spa = args->src_ip;
	cpmac(&(packet->tha[0]), args->trg_mac);
	packet->tpa = args->trg_ip;
}

int	main(int ac, char **av)
{
	int 			sock;
	t_args			args;
	t_arp			packet;
	uint8_t			*mac;

	if (parse_args(ac, av, &args) < 0)
		return (end(USAGE, -1));
	if (!(sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))))
		return (end("socket fucked.\n", -1));
	if ((mac = get_mac()) == NULL)
	{
		close(sock);
		return (end("get_mac error.\n", -1));
	}
	cpmac(&(packet.src_mac[0]), mac);
	free(mac);
	setup_packet(&args, &packet);
	if (wait_packet(sock) < 0)
	{
		close(sock);
		return (end("error while waiting packet.\n", -1));
	}
	close(sock);
	printf("everything went well.\n");
	return (0);
}
