#include "philo.h"

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*monitor(void *arg)
{
	int i;

	(void)arg;
	while (!vars()->dead)
	{
		i = 0;
		while (i < vars()->n_philo)
		{
			pthread_mutex_lock(&vars()->time);
			if (get_time() - vars()->philo[i]->lastmeal > vars()->ttdie)
			{
				printf("dif:%ld\nttd:%ld\n", get_time() -vars()->philo[i]->lastmeal, vars()->ttdie);
				pthread_mutex_lock(&vars()->print);
	        	printf("%ld %d died\n", get_time() - vars()->timestamp, vars()->philo[i]->n);
				vars()->dead = true;
				pthread_mutex_unlock(&vars()->print);
			}
			pthread_mutex_unlock(&vars()->time);
			i++;
		}
	}
	return (NULL);
}

void	eating_msg(t_philo *philo)
{
	pthread_mutex_lock(&vars()->print);
	pthread_mutex_lock(&vars()->time);
	printf("%ld %d is eating\n", get_time() - vars()->timestamp, philo->n);
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
	usleep(vars()->tteat * 1000); 
}
void	sleeping_msg(t_philo *philo)
{
	pthread_mutex_lock(&vars()->print);
	pthread_mutex_lock(&vars()->time);
	printf("%ld %d is sleeping\n", get_time() - vars()->timestamp, philo->n);
	pthread_mutex_unlock(&vars()->print);
	pthread_mutex_unlock(&vars()->time);
	usleep(vars()->ttsleep * 1000);
}

