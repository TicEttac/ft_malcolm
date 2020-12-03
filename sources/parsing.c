#include "ft_malcolm.h"

bool	hextoi(char i, uint8_t *ret)
{
	if (i >= '0' && i <= '9')
		*ret = (i - '0');
	else if (i <= 'f' && i >= 'a')
		*ret = (i - 'a' + 10);
	else if (i <= 'F' && i >= 'A')
		*ret = (i - 'A' + 10);
	else
		return (false);
	return (true);

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
		if (!(hextoi(str[i * 3], &tmp)))
		{
			free(ret);
			return (NULL);
		}
		ret[i] = tmp << 4;
		if (!(hextoi(str[i * 3 + 1], &tmp)))
		{
			free(ret);
			return (NULL);
		}
		ret[i] += tmp;
		i++;
	}
	return (ret);
}

int	parse_args(int ac, char **av, t_args *args)
{
	uint8_t	*tmp;

	if (ac != 5)
		return (-1);
	args->src_ip = inet_addr(av[1]);
	args->trg_ip = inet_addr(av[3]);
	tmp = strtomac(av[2]);
	if (memcpy(args->src_mac, tmp, 6) == NULL)
		return (-1);
	free(tmp);
	tmp = NULL;
	tmp = strtomac(av[4]);
	if (memcpy(args->trg_mac, tmp, 6) == NULL)
		return (-1);
	free(tmp);
	return (0);
}
