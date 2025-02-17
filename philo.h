/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:26:46 by framador          #+#    #+#             */
/*   Updated: 2025/02/16 20:12:13 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_philo
{
	bool			forks;
	int				n;
	long			lastmeal;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_vars
{
	int				n_philo;
	long			tteat;
	long			ttdie;
	long			ttsleep;
	long			status;
	int				nmeals;
	int				mealcount;
	int				i;
	long			timestamp;
	bool			dead;
	pthread_mutex_t	var;
	pthread_mutex_t	print;
	pthread_mutex_t	inc;
	pthread_mutex_t	time;
	pthread_mutex_t	m_philo;
	pthread_t		monitor;
	t_philo			**philo;
}	t_vars;
/*MATH*/

int		ft_atoi(char *str);
void	ft_usleep(long time_in_mls);

/*Initialization*/

t_vars	*vars(void);
bool	set_table(void);
bool	init_philo(void);
void	release_philo(void);
t_vars	*vars(void);
bool	init_mutexs(void);
void	thread_destroyer(void);

/*Routine*/

void	eating_msg(t_philo *philo);
void	sleeping_msg(t_philo *philo);
void	thinking_ms(t_philo *philo);
long	get_time(void);
void	*monitor(void *arg);
void	drop_forks(t_philo *philo);
bool	check_dead(void);

#endif