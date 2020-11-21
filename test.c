# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <ifaddrs.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <net/if.h>
# include <linux/if_ether.h>
/*
void	find_af_packet(struct ifaddrs *ifap)
{
	struct ifaddrs	*tmp;

	tmp = ifap;
	while (tmp && (tmp->ifa_addr->sa_family != AF_PACKET || tmp->ifa_addr->sa_family == AF_LOOPBACK))
		tmp = tmp->ifa_next;
	if (!tmp)
		return ;
	printf("valide interface name: %s\n", tmp->ifa_name);
	return ;

}
*/

	typedef struct s_arp
	{
	struct sockaddr	pa;
	struct sockaddr	ha;
	int		flag;
	}		t_arp;

int	main()
{
	t_arp		arp;
	int 		sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	unsigned char	*ptr = &arp.ha.sa_data[0];
	//perror(NULL);
	ioctl(sock, SIOCGARP, &arp);
	perror(NULL);
	for (int i=0; i < 5; i++)
		printf("%d:", ptr[i]);
	printf("\n");
	return (0);
}
