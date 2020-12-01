#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

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

# define AR_PROTOCOL 0x0806
# define REQUEST 1 << 4
# define REPLY 	2 << 4

typedef struct			s_args
{
	in_addr_t	src_ip;
	uint8_t		src_mac[6];
	in_addr_t	trg_ip;
	uint8_t		trg_mac[6];
}				t_args;

typedef struct			s_io
{
	struct sockaddr	pa;
	struct sockaddr	ha;
	int		flag;
}				t_io;

typedef struct			s_arp
{
	//HEADER
	uint8_t		dst_mac[6];
	uint8_t		src_mac[6];
	uint16_t	protocol;
	//DATA
	uint16_t	hrd;
	uint16_t	pro;
	uint8_t		hln;
	uint8_t		pln;
	uint16_t	op;
	uint8_t		sha[6];
	in_addr_t	spa;
	uint8_t		tha[6];
	in_addr_t	tpa;
} __attribute__((packed))	t_arp;

void	cpmac(uint8_t *dst, uint8_t src[6]);
int	parse_args(int ac, char **av, t_args *args);

#endif
