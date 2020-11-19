#include "ft_malcolm.h"

uint8_t	hextoi(char i)
{
	if (i > '0' && i < '9')
		return (i - '0');
	if (i < 'f' && i > 'a')
		return (i - 'a' + 9);
	if (i < 'F' && i > 'A')
		return (i - 'A' + 9);
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
		if ((ret[i] = hextoi(str[i * 3]) << 4) < 0)
		{
			free(ret);
			return (NULL);
		}
		if ((tmp = hextoi(str[i * 3 + 1])) < 0)
		{
			free(ret);
			return (NULL);
		}
		else
			ret[i] += tmp;
		i++;
	}
	return (ret);
}

int	parse_args(int ac, char **av, t_args *args)
{
	int	i;
	uint8_t	*tmp;

	i = 0;
	if (ac != 5)
		return (-1);
	args->src_ip = inet_addr(av[1]);
	args->trg_ip = inet_addr(av[3]);
	tmp = strtomac(av[2]);
	if (strcpy(args->src_mac, tmp) == NULL)
		return (-1);
	free(tmp);
	tmp = strtomac(av[4]);
	if (strcpy(args->trg_mac, tmp) == NULL)
		return (-1);
	free(tmp);
	return (0);
}
