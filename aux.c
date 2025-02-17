/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:16:47 by framador          #+#    #+#             */
/*   Updated: 2025/02/17 20:25:50 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		printf("%ld %d has taken a fork\n", get_time() - vars()->stime,
			philo->n);
	else
		printf("%ld %d is %s\n", get_time() - vars()->stime, philo->n, str);
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

void	init_times(void)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&vars()->time);
	vars()->stime = get_time();
	pthread_mutex_unlock(&vars()->time);
	while (i < vars()->n_philo)
	{
		pthread_mutex_lock(&vars()->time);
		vars()->philo[i]->lastmeal = vars()->stime;
		pthread_mutex_unlock(&vars()->time);
		i++;
	}
}
