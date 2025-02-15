/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:26:52 by framador          #+#    #+#             */
/*   Updated: 2025/02/15 21:00:33 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void grab_forks(t_philo *philo)
{
    int left = philo->n - 1;
    int right = (philo->n % vars()->n_philo);

    if (left < right)
    {
        pthread_mutex_lock(&vars()->philo[left]->fork);
        pthread_mutex_lock(&vars()->print);
        printf("%ld %d has taken a fork\n", get_time() - vars()->timestamp, philo->n);
        pthread_mutex_unlock(&vars()->print);
        pthread_mutex_lock(&vars()->philo[right]->fork);
        pthread_mutex_lock(&vars()->print);
        printf("%ld %d has taken a fork\n", get_time() - vars()->timestamp, philo->n);
        pthread_mutex_unlock(&vars()->print);
    }
    else
    {
        pthread_mutex_lock(&vars()->philo[right]->fork);
        pthread_mutex_lock(&vars()->print);
        printf("%ld %d has taken a fork\n", get_time() - vars()->timestamp, philo->n);
        pthread_mutex_unlock(&vars()->print);
        pthread_mutex_lock(&vars()->philo[left]->fork);
        pthread_mutex_lock(&vars()->print);
        printf("%ld %d has taken a fork\n", get_time() - vars()->timestamp, philo->n);
        pthread_mutex_unlock(&vars()->print);
    }
}

void drop_forks(t_philo *philo)
{
    int left = philo->n - 1;
    int right = (philo->n % vars()->n_philo);

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
	pthread_mutex_lock(&vars()->print);
	pthread_mutex_lock(&vars()->time);
	if (!ft_strcmp(str, "FORK"))
		printf("%ld %d has taken a fork\n", get_time() - vars()->timestamp, philo->n);
	else
		printf("%ld %d is %s\n", get_time() - vars()->timestamp, philo->n, str);
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
}
void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	printf("Philo:%d has arrived\n", philo->n);
	if (vars()->n_philo == 1)
	{
		printf("HERE\n");
		print_action(philo,"FORK");
		usleep(vars()->ttdie * 1000);
		return (NULL);		
	}
	if (philo->n % 2 == 0)
		usleep(100);
	while (!vars()->dead)
	{
		grab_forks(philo);
		eating_msg(philo);
		philo->lastmeal = get_time();
		drop_forks(philo);
		sleeping_msg(philo);
	}
	return (NULL);
}

void	init_times(void)
{
	int i;
	
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
	int i;

	i = 0;
	if (!init_philo())
		return (false);
	if (!init_mutexs())
		return (false);
	vars()->i = 0;
	vars()->dead = false;
	init_times();
	while (i < vars()->n_philo)
	{
		if (pthread_create(&vars()->philo[i]->thread, NULL, routine, (void*)vars()->philo[i])!= 0)
			return (false);
		i++;
	}
	pthread_create(&vars()->monitor, NULL, monitor, NULL);
	pthread_join(vars()->monitor , NULL);
	thread_destroyer();
	return (true);
}