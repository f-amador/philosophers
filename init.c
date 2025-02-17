/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:26:49 by framador          #+#    #+#             */
/*   Updated: 2025/02/16 19:55:06 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_philo(void)
{
	int	i;

	i = 0;
	vars()->philo = (t_philo **)malloc(vars()->n_philo * sizeof(t_philo *));
	if (!vars()->philo)
		return (false);
	while (i < vars()->n_philo)
	{
		vars()->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!vars()->philo[i])
			return (false);
		vars()->philo[i]->n = i + 1;
		vars()->philo[i]->meals = 0;
		if (pthread_mutex_init(&vars()->philo[i]->fork, NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

void	thread_destroyer(void)
{
	int	i;

	i = 0;
	while (i < vars()->n_philo)
	{
		pthread_join(vars()->philo[i]->thread, NULL);
		i++;
	}
}

void	release_philo(void)
{
	int	i;

	i = 0;
	while (vars()->philo && i < vars()->n_philo)
	{
		pthread_mutex_destroy(&vars()->philo[i]->fork);
		free(vars()->philo[i]);
		vars()->philo[i++] = NULL;
	}
	free(vars()->philo);
	pthread_mutex_destroy(&vars()->print);
	pthread_mutex_destroy(&vars()->time);
	pthread_mutex_destroy(&vars()->inc);
}

bool	init_mutexs(void)
{
	if (pthread_mutex_init(&vars()->print, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&vars()->inc, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&vars()->time, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&vars()->m_philo, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&vars()->var, NULL) != 0)
		return (false);
	return (true);
}
