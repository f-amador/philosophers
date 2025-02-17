/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:26:52 by framador          #+#    #+#             */
/*   Updated: 2025/02/17 20:27:40 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->n - 1;
	right = (philo->n % vars()->n_philo);
	if (left < right)
	{
		pthread_mutex_lock(&vars()->philo[left]->fork);
		pthread_mutex_lock(&vars()->philo[right]->fork);
	}
	else
	{
		pthread_mutex_lock(&vars()->philo[right]->fork);
		pthread_mutex_lock(&vars()->philo[left]->fork);
	}
	pthread_mutex_lock(&vars()->time);
	pthread_mutex_lock(&vars()->print);
	if (!check_dead())
	{
		printf("%ld %d grabbed a fork\n", get_time() - vars()->stime, philo->n);
		printf("%ld %d grabbed a fork\n", get_time() - vars()->stime, philo->n);
	}
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
}

void	drop_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->n - 1;
	right = (philo->n % vars()->n_philo);
	if (left < right)
	{
		pthread_mutex_unlock(&vars()->philo[right]->fork);
		pthread_mutex_unlock(&vars()->philo[left]->fork);
	}
	else
	{
		pthread_mutex_unlock(&vars()->philo[left]->fork);
		pthread_mutex_unlock(&vars()->philo[right]->fork);
	}
}

bool	routine_aux(t_philo *philo)
{
	if (check_dead())
		return (false);
	grab_forks(philo);
	if (check_dead())
	{
		drop_forks(philo);
		return (false);
	}
	pthread_mutex_lock(&vars()->m_philo);
	pthread_mutex_lock(&vars()->time);
	philo->lastmeal = get_time();
	pthread_mutex_unlock(&vars()->time);
	pthread_mutex_unlock(&vars()->m_philo);
	eating_msg(philo);
	drop_forks(philo);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (vars()->n_philo == 1)
	{
		print_action(philo, "FORK");
		ft_usleep(vars()->ttdie);
		return (NULL);
	}
	if (philo->n % 2 == 0)
		ft_usleep(3);
	while (1)
	{
		if (!routine_aux(philo))
			break ;
		if (check_dead())
			break ;
		sleeping_msg(philo);
		if (check_dead())
			break ;
		thinking_ms(philo);
	}
	return (NULL);
}

bool	set_table(void)
{
	int	i;

	i = 0;
	if (!init_philo())
		return (false);
	if (!init_mutexs())
		return (false);
	vars()->mealcount = 0;
	vars()->dead = false;
	init_times();
	while (i < vars()->n_philo)
	{
		if (pthread_create(&vars()->philo[i]->thread, NULL, routine,
				(void *)vars()->philo[i]) != 0)
			return (false);
		i++;
	}
	pthread_create(&vars()->monitor, NULL, monitor, NULL);
	pthread_join(vars()->monitor, NULL);
	thread_destroyer();
	return (true);
}
