#include "rt.h"

char			key_old(t_data data, int mask)
{
	if (data.input.key[mask] && data.input.oldkey[mask])
		return (1);
	return (0);
}

char			key_check(t_data data, int mask)
{
	if (data.input.key[mask] && !data.input.oldkey[mask])
		return (1);
	return (0);
}