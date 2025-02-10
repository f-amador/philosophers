
#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define INT_MAX 2147483647
#define INT_MIN -2147483648

typedef struct s_vars
{
	int	n_philo;
	int	tteat;
	int	ttdie;
	int	ttsleep;
	int	status;
}	t_vars;

typedef struct s_philo
{
	int			n;
	pthread_t	thread;
}	t_philo;

/*MATH*/

int	ft_atoi(char *str);


/*Initialization*/

t_vars *vars(void);
void	set_table(t_philo *philo);
void	*dinner_time(void *arg);

#endif