/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:58:23 by framador          #+#    #+#             */
/*   Updated: 2025/02/16 19:58:47 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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
	
	void	*monitor(void *arg)
	{
		int	i;

	(void)arg;
	while (1)
	{
		i = 0;
		while (i < vars()->n_philo)
		{
			pthread_mutex_lock(&vars()->time);
			pthread_mutex_lock(&vars()->print);
			if (get_time() - vars()->philo[i]->lastmeal > vars()->ttdie)
			{
				printf("%ld %d died\n", get_time() - vars()->timestamp,
				vars()->philo[i]->n);
				pthread_mutex_lock(&vars()->var);
				vars()->dead = true;
				pthread_mutex_unlock(&vars()->var);
				pthread_mutex_unlock(&vars()->print);
				pthread_mutex_unlock(&vars()->time);
				return (NULL);
			}
			pthread_mutex_unlock(&vars()->print);
			pthread_mutex_unlock(&vars()->time);
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
		ft_usleep(10);
	}
	return (NULL);
}

void	eating_msg(t_philo *philo)
{
	pthread_mutex_lock(&vars()->time);
	pthread_mutex_lock(&vars()->print);
	printf("%ld %d is eating\n", get_time() - vars()->timestamp, philo->n);
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
	printf("%ld %d is sleeping\n", get_time() - vars()->timestamp, philo->n);
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
	ft_usleep(vars()->ttsleep);
}

void	thinking_ms(t_philo *philo)
{
	pthread_mutex_lock(&vars()->time);
	pthread_mutex_lock(&vars()->print);
	printf("%ld %d is thinking\n", get_time() - vars()->timestamp, philo->n);
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
	ft_usleep(1);
}
