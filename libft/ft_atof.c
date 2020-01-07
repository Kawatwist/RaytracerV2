#include "libft.h"

double  ft_atof(const char *nptr)
{
	double		nbr;
	double		nbr2;
	long long	tmp;
	int			flag; 			// [neg][0][j][i]

	nbr2 = 0.0;
	flag = 0;				// Check Char
	if (!nptr || *nptr == '\0')
		return (0);
	if (*nptr == '-' || *nptr == '+')
	{
		flag = (*nptr == '-' ? 0b1000000000000000000000000 : 0); // Si le premier char == '-' on met la valeur 16777216 a notre variable (Neg actif) 
		nptr++;
	}
	while (nptr[flag & 0xFF] && ((nptr[flag & 0xFF] >= '0' && nptr[flag & 0xFF] <= '9') || nptr[flag & 0xFF] == '.')) // On avance tant que l'on es different des valeurs (Seulement sur le premier Byte)
		flag += 1; //Incrementation de i (1 << 0)
	if (!(nptr[flag & 0xFF] == '\0' || (nptr[flag & 0xFF] == ' ')))
		return (0.0);
	else
	{
		nbr = (double)ft_atoi(nptr);
		flag -= (flag & 0xFF);
		while (nptr[flag & 0xFF] != '.' && nptr[flag & 0xFF] != '\0' && nptr[flag & 0xFF] != ' ') // jai rajouter l'espace
			flag += 1;
		if ((flag & 0xFF) != 0 && nptr[flag & 0xFF] == '.')
		{
			nbr2 = (double)ft_atoi(&(nptr[(flag & 0xFF) + 1]));
			tmp = nbr2;			// Fonction Compte_nbr
			while (tmp)
			{
				tmp /= 10;
				flag += (1 << 8); // Incrementation de j
			}				// Fonction Power
			tmp = 1;
			while ((flag & 0xFF00))
			{
				tmp *= 10;
				flag -= (1 << 8); // Decrementation de j
			}
			nbr2 /= tmp;
			}
	}
	nbr = nbr + nbr2;
	if (flag & 0x1000000) // On check si le bit 0b000000001000000000000000000000000 est actif
		nbr *= -1;
	return (nbr);
}