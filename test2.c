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
# include <netpacket/packet.h>

uint8_t	hextoi(char i)
{
	if (i >= '0' && i <= '9')
		return (i - '0');
	if (i <= 'f' && i >= 'a')
		return (i - 'a' + 10);
	if (i <= 'F' && i >= 'A')
		return (i - 'A' + 10);
	return (-1);

}

uint8_t	*strtomac(char *str)
{
	size_t	i;
	uint8_t	*ret;
	uint8_t	tmp;

	i = 0;
	if (!(ret = malloc(6 * sizeof(ret))))
		return (NULL);
	while (i <= 5)
	{
		if ((tmp = hextoi(str[i * 3])) < 0)
		{
			free(ret);
			return (NULL);
		}
		ret[i] = tmp << 4;
		if ((tmp = hextoi(str[i * 3 + 1])) < 0)
		{
			free(ret);
			return (NULL);
		}
		ret[i] += tmp;
		i++;
	}
	return (ret);
}

int main()
{
	struct ifaddrs		*addr = NULL, *ptr = NULL;
	struct sockaddr_ll	*ll;
	int			i = 0;

	if (getifaddrs(&addr) < 0)
		perror("getifaddrs");
	else
	{
		ptr = addr;
		while (ptr)
		{
			if (ptr->ifa_addr && ptr->ifa_addr->sa_family == AF_PACKET)
			{
				ll = (struct sockaddr_ll *)ptr->ifa_addr;
				printf("::%s\n", ptr->ifa_name);
				i = 0;
				while (i < ll->sll_halen)
				{
					printf("%d:", (int)ll->sll_addr[i]);
					i++;
				}
				printf("\n");
			}
			ptr = ptr->ifa_next;
		}
		freeifaddrs(addr);
	}
	return (0);
}
