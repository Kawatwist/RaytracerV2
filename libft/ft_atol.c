#include "libft.h"

long long	ft_atol(const char *nptr)
{
	int		negative;
	long	nb;

	nb = 0;
	negative = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
		negative = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + (*nptr - '0');
		nptr++;
	}
	return (nb * negative);
}