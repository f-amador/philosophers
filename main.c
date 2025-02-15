/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framador <framador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:26:01 by framador          #+#    #+#             */
/*   Updated: 2025/02/15 18:19:40 by framador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_vars *vars(void)
{
	static t_vars init;

	return (&init);
}

bool	check_arguments(int argc, char **argv)
{
	vars()->n_philo = ft_atoi(argv[1]);
	vars()->ttdie = ft_atoi(argv[2]);
	vars()->tteat = ft_atoi(argv[3]);
	vars()->ttsleep = ft_atoi(argv[4]);
	if (argc == 6)
		vars()->nmeals = ft_atoi(argv[5]);
	else
		vars()->nmeals = -1;
	if (vars()->n_philo < 1 || vars()->ttdie < 1 || vars()->tteat < 1 || vars()->ttsleep < 1)
	{
		printf("INVALID INPUT\nAll values must be positives");
		return (false);
	}
	if (argc == 6 && vars()->nmeals < 1)
	{
		printf("INVALID INPUT\nAll values must be positives");
		return (false);
	}
	return (true);	
}

int	main(int argc, char *argv[])
{
	printf("HERE\n");
	if (argc != 5 && argc != 6)
		return (1 + 0 * printf("4 arguments required.\n ./philo x x x x\n"));
	if (!check_arguments(argc, argv))
		return (1);
	if(!set_table())
	{
		release_philo();
		return (1);
	}
	release_philo();
}