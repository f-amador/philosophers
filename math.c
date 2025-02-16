/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:52:33 by framador          #+#    #+#             */
/*   Updated: 2025/02/16 19:53:00 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time_in_mls)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_mls)
		usleep(500);
}

int	ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9'));
}

int	ft_atoi(char *str)
{
	long	res;
	int		i;
	int		sig;

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
	return ((int)(res * sig));
}
