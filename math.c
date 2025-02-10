#include "philo.h"

int	ft_isdigit(char c)
{
	return((c >= '0' && c <= '9'));
}

int	ft_atoi(char *str)
{
	long res;
	int i;
	int sig;

	i = 0;
	if (str[i] == '-')
		sig = -1;
	else
		sig = 1;
	res = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		res = res * 10 + (str[i] - '0');
		if (res * sig > INT_MAX || res * sig < INT_MIN)
			return (-1);
		i++;
	}
	printf("res:%ld\n", res);
	return ((int)(res * sig));
}
