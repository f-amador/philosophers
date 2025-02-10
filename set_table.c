#include "philo.h"

void	*dinner_time(void *arg)
{
	static int i;
	int p;
	(void)arg;
	printf("%d sat at the table thread\n", ++i);
	while(!vars()->status)
	{
	 	usleep(2 * p);
	}
	printf("Everyone present\n");
	return (NULL);
}

void	set_table(t_philo *philo)
{
	int i;

	i = 0;
	while (i < vars()->n_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, &dinner_time, NULL) != 0)
			exit(1);
		philo[i].n = i + 1;
		printf("philo number %d has been created\n", i + 1);
		i++;
		usleep(200 * i);
	}
	vars()->status = 1;
	i = 0;
	sleep(1);
	while (i < vars()->n_philo)
	{
		printf("Philo %d has thread %lu\n", philo[i].n, philo[i].thread);
		i++;
	}
}