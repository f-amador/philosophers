/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:58:23 by framador          #+#    #+#             */
/*   Updated: 2025/02/17 20:23:52 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	monitor_aux(t_philo *philo)
{
	pthread_mutex_lock(&vars()->time);
	pthread_mutex_lock(&vars()->print);
	if (get_time() - philo->lastmeal > vars()->ttdie)
	{
		printf("%ld %d died\n", get_time() - vars()->stime, philo->n);
		pthread_mutex_lock(&vars()->var);
		vars()->dead = true;
		pthread_mutex_unlock(&vars()->var);
		pthread_mutex_unlock(&vars()->print);
		pthread_mutex_unlock(&vars()->time);
		return (false);
	}
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
	return (true);
}

void	*monitor(void *arg)
{
	int	i;

	(void)arg;
	while (1)
	{
		i = 0;
		while (i < vars()->n_philo)
		{
			if (!monitor_aux(vars()->philo[i]))
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&vars()->var);
		if (vars()->dead)
		{
			pthread_mutex_unlock(&vars()->var);
			break ;
		}
		pthread_mutex_unlock(&vars()->var);
		if (vars()->nmeals != -1)
			count_meals();
		ft_usleep(1);
	}
	return (NULL);
}

void	eating_msg(t_philo *philo)
{
	pthread_mutex_lock(&vars()->time);
	pthread_mutex_lock(&vars()->print);
	if (!check_dead())
		printf("%ld %d is eating\n", get_time() - vars()->stime, philo->n);
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
	ft_usleep(vars()->tteat);
	pthread_mutex_lock(&vars()->m_philo);
	philo->meals++;
	pthread_mutex_unlock(&vars()->m_philo);
}

void	sleeping_msg(t_philo *philo)
{
	pthread_mutex_lock(&vars()->time);
	pthread_mutex_lock(&vars()->print);
	if (!check_dead())
		printf("%ld %d is sleeping\n", get_time() - vars()->stime, philo->n);
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
	ft_usleep(vars()->ttsleep);
}

void	thinking_ms(t_philo *philo)
{
	pthread_mutex_lock(&vars()->time);
	pthread_mutex_lock(&vars()->print);
	if (!check_dead())
		printf("%ld %d is thinking\n", get_time() - vars()->stime, philo->n);
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
	ft_usleep(10);
}
