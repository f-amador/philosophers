/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:52:33 by framador          #+#    #+#             */
/*   Updated: 2025/02/17 20:27:59 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time_in_mls)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_mls)
	{
		usleep(500);
		if (check_dead())
			break ;
	}
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

void	count_meals(void)
{
	int	i;
	int	meals_count;

	meals_count = 0;
	i = 0;
	while (i < vars()->n_philo)
	{
		pthread_mutex_lock(&vars()->m_philo);
		if (vars()->philo[i]->meals >= vars()->nmeals)
			meals_count++;
		pthread_mutex_unlock(&vars()->m_philo);
		i++;
	}
	if (meals_count == vars()->n_philo)
	{
		pthread_mutex_lock(&vars()->var);
		vars()->dead = true;
		pthread_mutex_unlock(&vars()->var);
		return ;
	}
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
