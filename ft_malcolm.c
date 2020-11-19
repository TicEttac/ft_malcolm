#include "ft_malcolm.h"

int	end(char *s, int ret)
{
	printf("%s", s);
	perror(NULL);
	if (errno)
		printf("errno : %d\n", errno);
	return (ret);

}

int main(int ac, char **av)
{
	t_args	args;

	if (parse_args(ac, av, &args) < 0)
		return (end("bad arguments.\n", -1));
	printf("mac ");
	int i = 0;
	while (i <= 5)
	{
		printf("%d ", args.src_mac[i]);
		i++;
	}
	printf("\n");
}
