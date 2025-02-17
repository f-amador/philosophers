/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:26:52 by framador          #+#    #+#             */
/*   Updated: 2025/02/16 20:18:50 by framador         ###   ########.fr       */
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
		pthread_mutex_lock(&vars()->time); 
		pthread_mutex_lock(&vars()->print);
		printf("%ld %d has taken a fork\n", get_time() - vars()->timestamp, philo->n);
		printf("%ld %d has taken a fork\n", get_time() - vars()->timestamp, philo->n);
		pthread_mutex_unlock(&vars()->print);
		pthread_mutex_unlock(&vars()->time); 
	}
	else
	{
		pthread_mutex_lock(&vars()->philo[right]->fork);
		pthread_mutex_lock(&vars()->philo[left]->fork);
		pthread_mutex_lock(&vars()->time); 
		pthread_mutex_lock(&vars()->print);
		printf("%ld %d has taken a fork\n", get_time() - vars()->timestamp, philo->n);
		printf("%ld %d has taken a fork\n", get_time() - vars()->timestamp, philo->n);
		pthread_mutex_unlock(&vars()->print);
		pthread_mutex_unlock(&vars()->time); 
	}
	if (check_dead())
		drop_forks(philo);
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&vars()->time);
	pthread_mutex_lock(&vars()->print);
	if (!ft_strcmp(str, "FORK"))
		printf("%ld %d has taken a fork\n", get_time() - vars()->timestamp,
			philo->n);
	else
		printf("%ld %d is %s\n", get_time() - vars()->timestamp, philo->n, str);
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
}

bool	check_dead(void)
{
	pthread_mutex_lock(&vars()->var);
	if (vars()->dead)
	{
		pthread_mutex_unlock(&vars()->var);
		return (1);
	}
	pthread_mutex_unlock(&vars()->var);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->n == 1)
	// {
	// 	printf("n_meals:%d\n", vars()->nmeals);
	// }
	if (vars()->n_philo == 1)
	{
		print_action(philo, "FORK");
		ft_usleep(vars()->ttdie);
		return (NULL);
	}
	if (philo->n % 2 == 0)
		ft_usleep(100);
	while (1)
	{
		if (check_dead())
			break ;
		grab_forks(philo);
		eating_msg(philo);
		pthread_mutex_lock(&vars()->m_philo);
		pthread_mutex_lock(&vars()->time);
		philo->lastmeal = get_time();
		pthread_mutex_unlock(&vars()->time);
		pthread_mutex_unlock(&vars()->m_philo);
		drop_forks(philo);
		if (check_dead())
			break ;
		sleeping_msg(philo);
		if (check_dead())
			break ;
		thinking_ms(philo);
	}
	return (NULL);
}

void	init_times(void)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&vars()->time);
	vars()->timestamp = get_time();
	pthread_mutex_unlock(&vars()->time);
	while (i < vars()->n_philo)
	{
		pthread_mutex_lock(&vars()->time);
		vars()->philo[i]->lastmeal = vars()->timestamp;
		pthread_mutex_unlock(&vars()->time);
		i++;
	}
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
